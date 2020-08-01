// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#include "azure_macro_utils/macro_utils.h"

#include "mu_has_comma_test.h"

#define EMPTY

#define M1()

#define M2(...) __VA_ARGS__

#define M3 ,

int run_mu_has_comma_tests(void)
{
    POOR_MANS_ASSERT(MU_HAS_COMMA() == 0);
    POOR_MANS_ASSERT(MU_HAS_COMMA(EMPTY) == 0);
    POOR_MANS_ASSERT(MU_HAS_COMMA(M1()) == 0);
    POOR_MANS_ASSERT(MU_HAS_COMMA(M1) == 0);
    POOR_MANS_ASSERT(MU_HAS_COMMA(M2) == 0);
    POOR_MANS_ASSERT(MU_HAS_COMMA(M2()) == 0);
    POOR_MANS_ASSERT(MU_HAS_COMMA(M2(A)) == 0);
    POOR_MANS_ASSERT(MU_HAS_COMMA(M2(A, B)) == 1);

    POOR_MANS_ASSERT(MU_HAS_COMMA(EMPTY, EMPTY) == 1);

    POOR_MANS_ASSERT(MU_HAS_COMMA(A) == 0);
    POOR_MANS_ASSERT(MU_HAS_COMMA(A B) == 0);

    POOR_MANS_ASSERT(MU_HAS_COMMA( , ) == 1);
    POOR_MANS_ASSERT(MU_HAS_COMMA(M3) == 1);
    POOR_MANS_ASSERT(MU_HAS_COMMA(A, ) == 1);
    POOR_MANS_ASSERT(MU_HAS_COMMA(, A) == 1);
    POOR_MANS_ASSERT(MU_HAS_COMMA(A, B) == 1);

    POOR_MANS_ASSERT(MU_HAS_COMMA(0, 0) == 1);
    POOR_MANS_ASSERT(MU_HAS_COMMA(/*123 zeros*/
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
