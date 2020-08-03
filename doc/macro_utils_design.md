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

### MU_HAS_COMMA(...)

`MU_HAS_COMMA` expands to 0 when the number of its arguments is 0 or 1. If the number of arguments is greater or equal to 2 then it expands to 0. Here' some examples

MU_HAS_COMMA() => 0

MU_HAS_COMMA(A) => 0

MU_HAS_COMMA(A, B) => 1

MU_HAS_COMMA("1", '2', 3) => 1

Here's how this works. Behind the scenes, `MU_HAS_COMMA` will call `MU_THE_NTH_ARG`(<<here are `MU_HAS_COMMA`'s arguments>>, 1, 1, 0)

MU_HAS_COMMA() => MU_THE_NTH_ARG( , 1, 1, 0) => 0
                                          ^
                                          |----- this is 4th argument. Note how the first argument is empty because __VA_ARGS__ expands to an empty token.

MU_HAS_COMMA(A) => MU_THE_NTH_ARG( A, 1, 1, 0) => 0
                                            ^
                                            |----- this is 4th argument.
                                    
MU_HAS_COMMA(A, B) => MU_THE_NTH_ARG( A, B, 1, 1, 0) => 1
                                               ^
                                               |----- this is 4th argument.

MU_HAS_COMMA("1", '2', 3) => MU_THE_NTH_ARG( "1", '2', 3, 1, 1, 0) => 1
                                                          ^
                                                          |----- this is 4th argument.

When called with more than 3 arguments, the macro does not produce 0 or 1, as in the case below:

MU_HAS_COMMA(X, Y, Z, T) => MU_THE_NTH_ARG( X, Y, Z, T, 1, 1, 0) => T
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

An empty preprocessor token still counts as a token, and `MU_HAS_COMMA(EMPTY)` still expands to "0" so `MU_HAS_COMMA` cannot be used straightforward for determining if a token is empty or not. In all the cases where `MU_HAS_COMMA` returns 1 obviously `MU_ISEMPTY` needs to return 0.

Enter MU_TRIGGER_PARENTHESIS(...). This is a macro that expands to `,` . This expansion, when passed to MU_HAS_COMMA produces "1".

The following constructs

`MU_TRIGGER_PARENTHESIS __VA_ARGS__ ()`

will expand to:

if __VA_ARGS__ is an empty token
    a) `MU_TRIGGER_PARENTHESIS __VA_ARGS__ ()` => `MU_TRIGGER_PARENTHESIS ()` => `,` (2 tokens, both empty). Passed to MU_HAS_COMMA => 1
    b) other reason why `MU_TRIGGER_PARENTHESIS __VA_ARGS__ ()` could expand to have a comma is because either
        1) `__VA_ARGS__ ()` expanded to have a comma or
        2) `MU_TRIGGER_PARENTHESIS __VA_ARGS__` expanded to have a comma. 
    In both cases "1" and "2" the macro is not empty. (these are not the droids we're looking for).

The combination of `MU_HAS_COMMA` + `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS __VA_ARGS__ ())` + `MU_HAS_COMMA(__VA_ARGS__ ())` + `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS __VA_ARGS__)` are all set in a dispath table from which the final result of `MU_ISEMPTY` is deduced.

Here are some examples of how this works:
                   `MU_HAS_COMMA`               `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS __VA_ARGS__ ())`           `MU_HAS_COMMA(__VA_ARGS__ ())`         `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS __VA_ARGS__)`

MU_ISEMPTY() = >        0                       `MU_HAS_COMMA((MU_TRIGGER_PARENTHESIS())`                       `MU_HAS_COMMA(())`                     `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS)`
                        0                       `MU_HAS_COMMA(,)                                                0                                       0
                        0                       1                                                               0                                       0

MU_ISEMPTY(A)=>         0                       `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS A ())`                     `MU_HAS_COMMA(A())`                     `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS A)`
                        0                       0                                                               0                                        0

#define M6() , /*note here, only M6 followed by () expands to ",", otherwise M6 stays as it is
MU_ISEMPTY(M6)=>        0                       `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS M6 ())`                    `MU_HAS_COMMA(M6())`                    `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS M6)`
                        0                       `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS ,    )`                    `MU_HAS_COMMA(,)`                       `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS M6)`
                        0                       1                                                               1                                       0

MU_ISEMPTY(() Z)=>      0                       `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS () Z)`                     `MU_HAS_COMMA(() Z())`                  `MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS () Z)`
                        0                       `MU_HAS_COMMA( , Z )`                                           `MU_HAS_COMMA(() Z())`                  `MU_HAS_COMMA(, Z)`
                        0                       1                                                               0                                       1



Here is how the "dispatch table" looks like for the `MU_ISEMPTY` macro:

`#define MU_ISEMPTY(...) MU_C5(MU_DISPATCH_EMPTY_, MU_HAS_COMMA(__VA_ARGS__), MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS __VA_ARGS__ ()), MU_HAS_COMMA(__VA_ARGS__ ()), MU_HAS_COMMA(MU_TRIGGER_PARENTHESIS __VA_ARGS__))`

MU_C5 just pastes together its 5 arguments resulting in one of the below definitions:

#define MU_DISPATCH_EMPTY_1000 0 /*not empty because MU_HAS_COMMA says there's a comma somewhere*/
#define MU_DISPATCH_EMPTY_1001 0
#define MU_DISPATCH_EMPTY_1010 0
#define MU_DISPATCH_EMPTY_1011 0
#define MU_DISPATCH_EMPTY_1100 0
#define MU_DISPATCH_EMPTY_1101 0
#define MU_DISPATCH_EMPTY_1110 0
#define MU_DISPATCH_EMPTY_1111 0

#define MU_DISPATCH_EMPTY_0100 1 /*empty because MU_TRIGGER_PARENTHESIS expanded to , (2 empty tokens) and __VA_ARGS__() did not have a comma and MU_TRIGGER_PARENTHESIS __VA_ARGS__ did not have a comma either*/
#define MU_DISPATCH_EMPTY_0101 0 
#define MU_DISPATCH_EMPTY_0110 0
#define MU_DISPATCH_EMPTY_0111 0
#define MU_DISPATCH_EMPTY_0000 0
#define MU_DISPATCH_EMPTY_0001 0
#define MU_DISPATCH_EMPTY_0010 0
#define MU_DISPATCH_EMPTY_0011 0



### MU_COUNT_ARG (...)
`MU_COUNT_ARG(...)` returns the number of arguments (including 0!) that are passed as arguments. Again, this should rather been seen as "number of commas -1" in the context of the preprocessor.

Here's how it works. `MU_COUNT_ARG` will build sort of an "if" statement like below:

`#define MU_COUNT_ARG(...) MU_C2(MU_COUNT_ARG_, MU_ISEMPTY(__VA_ARGS__))(__VA_ARGS__)`

It is based on `MU_ISEMPTY`: 
    a) if `MU_ISEMPTY` expands to "1" then `MU_COUNT_ARG` will expand to `MU_COUNT_ARG_1(__VA_ARGS__)`. `MU_COUNT_ARG_1` always expands to 0.
    b) if `MU_ISEMPTY` expands to "0" then `MU_COUNT_ARG` will expand to `MU_COUNT_ARG_0(__VA_ARGS__)`. `MU_COUNT_ARG_0(__VA_ARGS__)` further expands to `MU_COUNT_1_OR_MORE_ARG(__VA_ARGS__)` which will return the number of arguments.









































































