// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/*file containing all sort of tests that usually originate in upstream projects, brought here for dissemination*/

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_expand_no_expand_test.h"

// For gcc build that causes a false negative
#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wunused-value"
#endif

#define TRUEB 1,2,3 /*clearly something that contains a COMMA - even more than 1*/
#define FALSEB 4 /*clearly something that does NOT contains a comma*/

/*the below commented text SHOULD expand to 1,2,3 or to 4 depending on the condition*/
/*but error C4002: too many arguments for function-like macro invocation 'MU_IF0'*/
/*static int a[] = { MU_IF(0, TRUEB, FALSEB) };*/

/*MU_EXPAND, MU_NOEXPAND to the rescue!*/
/*static int a[] = { MU_EXPAND(MU_IF(0, MU_NOEXPAND(TRUEB), MU_NOEXPAND(FALSEB))) };*/

#if !defined(_MSC_VER) || (_MSC_VER >= 1920 )
/*MU_EXPAND/MU_NOEXPAND pair*/
static int a_TRUEBRANCH[] = { MU_EXPAND(MU_IF(1, MU_NOEXPAND(TRUEB), MU_NOEXPAND(FALSEB))) };
static int a_FALSEBRANCH[] = { MU_EXPAND(MU_IF(0, MU_NOEXPAND(TRUEB), MU_NOEXPAND(FALSEB))) };
#endif
int run_mu_expand_no_expand_tests(void)
{

    int a = MU_EXPAND(MU_NOEXPAND(1));
    POOR_MANS_ASSERT(a == 1);

    int a2 = (MU_EXPAND(MU_NOEXPAND(1, 3))); /*a2 = (1,3)*/
    POOR_MANS_ASSERT(a2 == 3);

#if !defined(_MSC_VER) || (_MSC_VER >= 1920 )
    /*MU_EXPAND/MU_NOEXPAND pair*/
    POOR_MANS_ASSERT(sizeof(a_TRUEBRANCH) / sizeof(a_TRUEBRANCH[0]) == 3);
    POOR_MANS_ASSERT(a_TRUEBRANCH[0] == 1);
    POOR_MANS_ASSERT(a_TRUEBRANCH[1] == 2);
    POOR_MANS_ASSERT(a_TRUEBRANCH[2] == 3);

    POOR_MANS_ASSERT(sizeof(a_FALSEBRANCH) / sizeof(a_FALSEBRANCH[0]) == 1);
    POOR_MANS_ASSERT(a_FALSEBRANCH[0] == 4);

    POOR_MANS_ASSERT(MU_ISEMPTY(MU_EXPAND(MU_NOEXPAND()))==1);
#endif
    return 0;
}
