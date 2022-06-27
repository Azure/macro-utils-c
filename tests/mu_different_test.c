// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <string.h>
#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_different_test.h"

/*uncomment line below to run some code with side-effects*/
//#define RUN_FUN_TESTS

#ifdef RUN_FUN_TESTS

/*due to side effects consequences MU_DIFFERENT(f(), g()); yields -1.*/
static int f_value = 3;
static int f(void)
{
    f_value--;
    (void)printf("f returning %d\n", f_value);
    return f_value;
}

static int g_value = 2;
static int g(void)
{
    g_value--;
    (void)printf("g returning %d\n", g_value);
    return g_value;
}
#endif

int run_mu_different_tests(void)
{
    int result = 0;

    POOR_MANS_ASSERT(MU_DIFFERENT(-2) != -2);

    POOR_MANS_ASSERT(MU_DIFFERENT(-1) != -1);

    POOR_MANS_ASSERT(MU_DIFFERENT(0) != 0);

    POOR_MANS_ASSERT(MU_DIFFERENT(1) != 1);

    POOR_MANS_ASSERT(MU_DIFFERENT(2) != 2);

    POOR_MANS_ASSERT(
        (MU_DIFFERENT(2, 3) != 2) &&
        (MU_DIFFERENT(2, 3) != 3)
    );

    POOR_MANS_ASSERT(
        (MU_DIFFERENT(3, 2) != 2) &&
        (MU_DIFFERENT(3, 2) != 3)
    );

    POOR_MANS_ASSERT(
        (MU_DIFFERENT(0, 1) != 0) &&
        (MU_DIFFERENT(0, 1) != 1)
    );

    POOR_MANS_ASSERT(
        (MU_DIFFERENT(1, 0) != 0) &&
        (MU_DIFFERENT(1, 0) != 1)
    );

    POOR_MANS_ASSERT(
        (MU_DIFFERENT(0, 1, 2) != 0) &&
        (MU_DIFFERENT(0, 1, 2) != 1) &&
        (MU_DIFFERENT(0, 1, 2) != 2)
    );

    /*works with floats too*/
    POOR_MANS_ASSERT(
        (MU_DIFFERENT(0.5) != 0.5)
    );

    POOR_MANS_ASSERT(
        (MU_DIFFERENT(0.5, 0) != 0.5) &&
        (MU_DIFFERENT(0.5, 0) != 0)
    );
    

    /*Is MU_DIFFERENT a constant-expression? (arrays in C con only have constant-expression sizes... until Microsoft will implement int a[b]*/

#define L1 0,1,2,3

    int a1[MU_DIFFERENT(L1)];
    (void)a1;

#define L2 1,2,3

    int a2[MU_DIFFERENT(L2) == 0 ? 1 : MU_DIFFERENT(L2)];
    (void)a2;

    /*works with variables too, but evaluated at runtime, obviously*/
    int a = 2; 
    int b = 22;
    POOR_MANS_ASSERT(
        (MU_DIFFERENT(a, b) != a) &&
        (MU_DIFFERENT(a, b) != b)
    );

#ifdef RUN_FUN_TESTS
    /*"for fun"*/
    int different = MU_DIFFERENT(f(), g());
    (void)different;
#endif

    return result;
}
