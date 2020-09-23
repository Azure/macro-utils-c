// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/*file containing all sort of tests that usually originate in upstream projects, brought here for dissemination*/

#include "test_helper.h"

#include "azure_macro_utils/macro_utils.h"

#include "mu_for_each_1_paste_test.h"

#define SUM_PAIR(a,b) a+b,
#define DIF_PAIR(a,b) a-b,

static int sums[] = { MU_FOR_EACH_1_PASTE(SUM_, PAIR(2,2), PAIR(3,5)) };

static int difs[] = { MU_FOR_EACH_1_PASTE(DIF_, PAIR(2,2), PAIR(6,2)) };

int run_mu_for_each_1_paste_test(void)
{
    POOR_MANS_ASSERT(sizeof(sums) / sizeof(sums[0]) == 2);
    POOR_MANS_ASSERT(sums[0] == 4);
    POOR_MANS_ASSERT(sums[1] == 8);
 
    POOR_MANS_ASSERT(sizeof(difs) / sizeof(difs[0]) == 2);
    POOR_MANS_ASSERT(difs[0] == 0);
    POOR_MANS_ASSERT(difs[1] == 4);

    return 0;
}
