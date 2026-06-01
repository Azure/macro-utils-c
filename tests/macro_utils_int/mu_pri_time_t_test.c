// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_pri_time_t_test.h"

/*test will test that time_t, as captured at the time of the test, can be printed*/
int run_mu_pri_time_t_tests(void)
{
    int result = 0;

    char temp[100];

    {/*0*/
        time_t now = time(NULL);
        int r = snprintf(temp, sizeof(temp), "%" PRI_TIME_T "", TIME_T_VALUE(now));
        POOR_MANS_ASSERT((r >= 0) && (r < sizeof(temp)));
        POOR_MANS_ASSERT(strchr(temp, '\n')==NULL); /*must not contain \n*/
    }

    return result;
}
