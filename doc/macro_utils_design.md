macro utils design
=======

Macro utils is a set of C useful macros.

This document explains how it was build and what every macro does. IN supporting understand rather than code accuracy, some macros will be chopped to deal with a reasonable number of arguments rather than their implementation that usually supports above 120 arguments.

### MU_THE_NTH_ARG(...)

`MU_THE_NTH_ARG` produces the nth argument that is passed to the macro. In the implementation case, "n" is 124 and that was determined empirically to be a safe limit with all preprocessors.

Assuming "n" is 4, here's some examples of what the output of the macro is

MU_THE_NTH_ARG(1,2,3,4) => 4

MU_THE_NTH_ARG(11, 22, 33, 44, 55) => 44

MU_THE_NTH_ARG(11, 22, 33) => error, the macro requires 4 or more arguments. This is ok, because in all the context where this macro is called, there will be more than 4 arguments passed to it.

`MU_THE_NTH_ARG` is not extremely useful by itself. When used with `MU_COUNT_1_OR_MORE_ARG` it becomes very useful.

### MU_COUNT_1_OR_MORE_ARG(...)

`MU_COUNT_1_OR_MORE_ARG` counts ("expands to a number") the number of the arguments passed to it. In all instances where this macro is called, there must be at least 1 argument passed to it.

Here's some examples:

MU_COUNT_1_OR_MORE_ARG(X) => 1

MU_COUNT_1_OR_MORE_ARG(a,b) => 2

MU_COUNT_1_OR_MORE_ARG(a, ,c) => 3

Here is how that is achieved. We're going to call `MU_THE_NTH_ARG`(<<here are `MU_COUNT_1_OR_MORE_ARG`'s arguments>>, 3,2,1).

Here's how it works for the examples above:
MU_COUNT_1_OR_MORE_ARG(X) => MU_THE_NTH_ARG(X, 3, 2, 1) => 1.
                                                     ^
                                                     |----- this is 4th argument

MU_COUNT_1_OR_MORE_ARG(a,b) => MU_THE_NTH_ARG(a, b, 3, 2, 1) => 2.
                                                       ^
                                                       |----- this is 4th argument

MU_COUNT_1_OR_MORE_ARG(a, ,c) => MU_THE_NTH_ARG(a, , c, 3, 2, 1) => 3
                                                        ^
                                                        |----- this is 4th argument

So what happens if the macro is called with more than 4 arguments? Such as a,b,c,d,e?

MU_COUNT_1_OR_MORE_ARG(a, ,c) => MU_THE_NTH_ARG(a, b, c, d, e, 3, 2, 1) => d
                                                         ^
                                                         |----- this is 4th argument

Obviously `d` is not the expected macro expansion at this moment. So the macro has some limitations, it can count only 1...3 arguments. (it can count 1..n-1, where n is coming from `MU_THE_NTH_ARG`)

So what happens if the macro is called with 0 arguments?
MU_COUNT_1_OR_MORE_ARG() => MU_THE_NTH_ARG( , 3, 2, 1) => 1
                                                    ^
                                                    |----- this is 4th argument
                                                
Here we see how the macro does not produce 0, and that is precisely why the macro is called MU_COUNT_**1**_OR_MORE_ARG. 

Next question is : how to produce 0 as a count result? Not easy or immediately stright forward. More macros are needed for that.

### MU_MORE_THAN_1_ARG(...)

`MU_MORE_THAN_1_ARG` expands to 0 when the number of its arguments is 0 or 1. If the number of arguments is greater or equal tot 2 then it expands to 0. Here' some examples

MU_MORE_THAN_1_ARG() => 0

MU_MORE_THAN_1_ARG(A) => 0

MU_MORE_THAN_1_ARG(A, B) => 1

MU_MORE_THAN_1_ARG("1", '2', 3) => 1

Here's how this works. Behind the scenes, `MU_MORE_THAN_1_ARG` will call `MU_THE_NTH_ARG`(<<here are `MU_MORE_THAN_1_ARG`'s arguments>>, 1, 1, 0)

MU_MORE_THAN_1_ARG() => MU_THE_NTH_ARG( , 1, 1, 0) => 0
                                                ^
                                                |----- this is 4th argument. Note how the first argument is empty because __VA_ARGS__ expands to an empty token.

MU_MORE_THAN_1_ARG(A) => MU_THE_NTH_ARG( A, 1, 1, 0) => 0
                                                  ^
                                                  |----- this is 4th argument.
                                    
MU_MORE_THAN_1_ARG(A, B) => MU_THE_NTH_ARG( A, B, 1, 1, 0) => 1
                                                     ^
                                                     |----- this is 4th argument.

MU_MORE_THAN_1_ARG("1", '2', 3) => MU_THE_NTH_ARG( "1", '2', 3, 1, 1, 0) => 1
                                                                ^
                                                                |----- this is 4th argument.

When called with more than 3 arguments, the macro does not produce 0 or 1, as in the case below:

MU_MORE_THAN_1_ARG(X, Y, Z, T) => MU_THE_NTH_ARG( X, Y, Z, T, 1, 1, 0) => T
                                                           ^
                                                           |----- this is 4th argument.


### MU_ISEMPTY(...)

`MU_ISEMPTY` expands to 1 if its variables arguments is an empty token or not. The simplest way to produce an empty token is to have a missing macro argument, like this: M(1, ,3). Note the second argument to the `M` macro is an empty token. Or if M is

```c
#define M(...) __VA_ARGS__

M() <= will expand to an empty processing token
```

or if M is
```c
#define EMPTY
#define M(...) EMPTY
```

An empty preprocessor token still counts as a token, and `MU_MORE_THAN_1_ARG(EMPTY)` still expands to "0" so `MU_MORE_THAN_1_ARG` cannot be used straightforward for determining if a token is empty or not. In all the cases where `MU_MORE_THAN_1_ARG` returns 1 obviously `MU_ISEMPTY` needs to return 0.

Enter MU_TRIGGER_PARENTHESIS(...). This is a macro that expands to `,` . This expansion, when passed to MU_MORE_THAN_1_ARG produces "1".

The following constructs

`MU_TRIGGER_PARENTHESIS __VA_ARGS__ ()`

will expand to:

if __VA_ARGS__ is an empty token
    a) `MU_TRIGGER_PARENTHESIS __VA_ARGS__ ()` => `MU_TRIGGER_PARENTHESIS ()` => `,` (2 tokens). Passed to MU_COUNT_MORE_THAN_1_ARG => 1
    b) `MU_TRIGGER_PARENTHESIS __VA_ARGS__ ()` => `MU_TRIGGER_PARENTHESIS WHATEVER()` => , . Passed to MU_COUNT_MORE_THAN_1_ARG => unknown number.

But based on `MU_MORE_THAN_1_ARG(__VA_ARGS__) and MU_TRIGGER_PARENTHESIS __VA_ARGS__ () the following table can be build

| MU_MORE_THAN_1_ARG(__VA_ARGS__) | MU_MORE_THAN_1_ARG(MU_TRIGGER_PARENTHESIS __VA_ARGS__ ()) | MU_ISEMPTY
|---------------------------------|-----------------------------------------------------------|-------------
|             1                   |  any(previous column already says there's more)           |      0
|             0                   |                              1                            |      0
|             0                   |                              0                            |      maybe 1


























































































