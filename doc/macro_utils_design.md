macro utils design
=======

Macro utils is a set of C useful macros.

This document explains how it was build and what every macro does. In supporting understandability rather than code accuracy, some macros will be chopped to deal with a reasonable number of arguments rather than their implementation that usually supports above 140 arguments.

### MU_THE_NTH_ARG(...)

`MU_THE_NTH_ARG` produces the nth argument that is passed to the macro. In the implementation case, "n" is 140 and that was determined empirically to be a safe limit with all preprocessors.

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

Next question is : how to produce 0 as a count result? Not easy or immediately straight forward. More macros are needed for that.

### MU_ISEMPTY(...)

`MU_ISEMPTY` expands to 1 if its variables arguments is empty. Otherwise it expands to 0. It uses `__VA_OPT__` which is available with all the C preprocessors that we currently use (MSVC, gcc).

### MU_COUNT_ARG (...)
`MU_COUNT_ARG(...)` returns the number of arguments (including 0!) that are passed as arguments.

Here's how it works. `MU_COUNT_ARG` will build sort of an "if" statement like below:

`#define MU_COUNT_ARG(...) MU_C2(MU_COUNT_ARG_, MU_ISEMPTY(__VA_ARGS__))(__VA_ARGS__)`

It is based on `MU_ISEMPTY`:
    a) if `MU_ISEMPTY` expands to "1" then `MU_COUNT_ARG` will expand to `MU_COUNT_ARG_1(__VA_ARGS__)`. `MU_COUNT_ARG_1` always expands to 0.
    b) if `MU_ISEMPTY` expands to "0" then `MU_COUNT_ARG` will expand to `MU_COUNT_ARG_0(__VA_ARGS__)`. `MU_COUNT_ARG_0(__VA_ARGS__)` further expands to `MU_COUNT_1_OR_MORE_ARG(__VA_ARGS__)` which will return the number of arguments.



### MU_EXPAND/MU_NOEXPAND
`MU_EXPAND/MU_NOEXPAND` is a pair a macro such as `MU_EXPAND(MU_NOEXPAND(x))` expands to `x`. All other arguments to `MU_EXPAND` (except `MU_NOEXPAND`) are invalid. MU_NOEXPAND itself is a simple token, so it doesn't expand by itself to anything that is, `MU_NOEXPAND(x)` expands to `MU_NOEXPAND(x)`. This is intended, and likely will cause a compilation error.

Here's why MU_EXPAND/MU_NOEXPAND are useful. In the context of macros (such as `MU_IF`) that expand to one thing or the other, when one of the "things" contains a comma, the whole macro is invalid. For example:

```c
#define TRUEB 1,2,3 /*notice commas*/
#define FALSEB 4

MU_IF(1, TRUEB, FALSEB)
```

In the code above the intention is to have MU_IF expand to 1,2,3. Well - since 1,2,3 contains commas, the macro is invalid as written. The solution is to capture the true branch / false branch in `MU_NOEXPAND` and provide `MU_NOEXPAND` later to `MU_EXPAND`, like below:

`MU_EXPAND(MU_IF(1, MU_NOEXPAND(TRUEB), MU_NOEXPAND(FALSEB)))`. The macro will expand to `MU_EXPAND(MU_NOEXPAND(1,2,3))` which will then expand to 1,2,3.

### MU_FOR_EACH_1_PASTE
```c
MU_FOR_EACH_1_PASTE(PASTE, ...)
```

`MU_FOR_EACH_1_PASTE` is a macro that expands to `PASTE` concatenated to every variadic argument. Here's an example:

`MU_FOR_EACH_1_PASTE(1, 1,2,3)` => 11 12 13

### MU_DIFFERENT
```c
MU_DIFFERENT(a,b,c)
```

`MU_DIFFERENT` is a macro that expands to a value that is different from any of the arguments. Depending on the arguments, evaluation can be done by the compiler at compile time, or at runtime.

Note: Not all argument types can be used ("strings" should not be used). Constant expressions are always useable. Arguments that are expressions with side-effects are unadvised.

Example:
MU_DIFFERENT(1) => 0
MU_DIFFERENT(0,1) => 2

Internally `MU_DIFFERENT` proposes numbers starting with MU_COUNT_ARG..0 as candidates for the expression result.

If one of these numbers is not equal to any of the arguments then `MU_DIFFERENT` will evaluate to this number.

### MU_STATIC_ASSERT
```c
MU_STATIC_ASSERT(CONDITION)
```

`MU_STATIC_ASSERT` evaluates the condition CONDITION and produces a compiler error if the condition is false.


### PRI_KB / KB_VALUE

`PRI_KB` is a printf format specifier that produces "nice" formatting of values (uint64_t) in KB or MB or GB. If the value would contain a fractional part, and that fractional part would start with 0, then the fractional part is not printed. Otherwiuse the first decimal of the fractional part is printed. Values less than 1KB are printed with all digits. For example:

The number 1025 (which is barely above 1KB) would be printed as 1 KB, not 1.0 KB.

The number 1048576 (this is precisley 1 MB) would be printed as 1 MB.

The number 1048575 (this is 1 MB - 1 byte) would be printed as 1023.9 KB.

`PRI_KB` used with numbers greater than 1024 GB will produce GB resolution. (`PRI_KB` can be easily expanded to handle TB resolution as well).

Here's some more examples of such formatting:

```c
    1023 => "1023 B"
    2048 => "2 KB"
    1048576 => "1 MB"
    2199023255551 => "2047.9 GB"
    10995116277760 => "10240 GB"
```

Note: due to computations done in the macro, the maximum value that can be formatted is ~ `UINT64_MAX` / 10.
