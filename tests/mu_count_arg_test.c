// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_count_arg_test.h"

#define EMPTY

int run_mu_count_arg_tests(void)
{
    POOR_MANS_ASSERT(MU_COUNT_ARG() == 0);
    POOR_MANS_ASSERT(MU_COUNT_ARG(EMPTY) == 0);

    POOR_MANS_ASSERT(MU_COUNT_ARG(A) == 1);
    POOR_MANS_ASSERT(MU_COUNT_ARG(()A) == 1);
    POOR_MANS_ASSERT(MU_COUNT_ARG(()) == 1);
    POOR_MANS_ASSERT(MU_COUNT_ARG(A()) == 1);
    POOR_MANS_ASSERT(MU_COUNT_ARG(A B) == 1);
    POOR_MANS_ASSERT(MU_COUNT_ARG(A ()) == 1);
    POOR_MANS_ASSERT(MU_COUNT_ARG(() A) == 1);

    POOR_MANS_ASSERT(MU_COUNT_ARG(,) == 2);
    POOR_MANS_ASSERT(MU_COUNT_ARG(A, ) == 2);
    POOR_MANS_ASSERT(MU_COUNT_ARG(, B) == 2);
    POOR_MANS_ASSERT(MU_COUNT_ARG(A, B) == 2);

    POOR_MANS_ASSERT(MU_COUNT_ARG(()A, B) == 2);
    POOR_MANS_ASSERT(MU_COUNT_ARG(A(), B) == 2);
    POOR_MANS_ASSERT(MU_COUNT_ARG(A, ()B) == 2);
    POOR_MANS_ASSERT(MU_COUNT_ARG(A, B()) == 2);
    

    return 0;
}
