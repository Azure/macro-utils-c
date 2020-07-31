// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#include "azure_macro_utils/macro_utils.h"

#include "mu_more_than_1_arg_test.h"

#define EMPTY

#define M1()

#define M2(...) __VA_ARGS__

int run_mu_more_than_1_arg_tests(void)
{
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG() == 0);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(EMPTY) == 0);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(M1()) == 0);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(M1) == 0);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(M2) == 0);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(M2()) == 0);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(M2(A)) == 0);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(M2(A, B)) == 1);

    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(EMPTY, EMPTY) == 1);

    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(A) == 0);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(A B) == 0);

    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG( , ) == 1);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(A, ) == 1);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(, A) == 1);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(A, B) == 1);

    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(0, 0) == 1);
    POOR_MANS_ASSERT(MU_MORE_THAN_1_ARG(/*123 zeros*/
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
        ) == 1);
    return 0;
}
