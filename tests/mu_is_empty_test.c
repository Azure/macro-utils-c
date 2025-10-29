// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_is_empty_test.h"

#define M1

#define M2(...)

#define M3(...) X

#define M4(...) Y, Z

#define M5(...) __VA_ARGS__

#define M6() ,

int run_mu_is_empty_tests(void)
{
    POOR_MANS_ASSERT(MU_ISEMPTY() == 1);

    POOR_MANS_ASSERT(MU_ISEMPTY(M1) == 1);

    POOR_MANS_ASSERT(MU_ISEMPTY(M2) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY(M2()) == 1);
    POOR_MANS_ASSERT(MU_ISEMPTY(M2(A)) == 1);
    POOR_MANS_ASSERT(MU_ISEMPTY(M2(A, B)) == 1);

    POOR_MANS_ASSERT(MU_ISEMPTY(M3) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY(M3(A)) == 0);

    POOR_MANS_ASSERT(MU_ISEMPTY(M4) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY(M4(A)) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY(M4(A, B)) == 0);

    POOR_MANS_ASSERT(MU_ISEMPTY(M5) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY(M5()) == 1);
    POOR_MANS_ASSERT(MU_ISEMPTY(M5(A)) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY(M5(A, B)) == 0);

    /*().. (())*/
    POOR_MANS_ASSERT(MU_ISEMPTY(()) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY((())) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY((), A) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY(,) == 0);
    POOR_MANS_ASSERT(MU_ISEMPTY(() A ) == 0);

    POOR_MANS_ASSERT(MU_ISEMPTY((A)) == 0);

    POOR_MANS_ASSERT(MU_ISEMPTY( M6 ) == 0);

    POOR_MANS_ASSERT(MU_ISEMPTY(() Z) == 0);

    return 0;
}
