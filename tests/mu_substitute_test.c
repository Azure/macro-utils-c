// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#include "azure_macro_utils/macro_utils.h"

#include "mu_substitute_test.h"

#define DIF(x,y) ((x)-(y))
#define MUL(x,y) ((x)*(y))

#define MU_IS_SUBST_PAIR


#define DO_MUL_IN_ARRAY(X) MU_SUBSTITUTE_L3(X, MUL) , /*note: a comma is needed between the array elements */

int run_mu_substitute_test(void)
{

    int a = MU_SUBSTITUTE_L1(PAIR(5,4), DIF); /*note: substitute PAIR(5,4) with DIF(5,4) which results in "1"*/
    POOR_MANS_ASSERT(a == 1);

    int b = MU_SUBSTITUTE_L2(PAIR(5, 4), MUL); /*note: substitute PAIR(5,4) with MUL(5,4) which results in "20"*/
    POOR_MANS_ASSERT(b == 20);

    /*a more complicated example*/
    int c[] = { MU_FOR_EACH_1(DO_MUL_IN_ARRAY, PAIR(1, 2), PAIR(3, 4), PAIR(5, 6)) };

    POOR_MANS_ASSERT(sizeof(c)/sizeof(c[0]) == 3);
    POOR_MANS_ASSERT(c[0] == 2);
    POOR_MANS_ASSERT(c[1] == 12);
    POOR_MANS_ASSERT(c[2] == 30);
    return 0;
}