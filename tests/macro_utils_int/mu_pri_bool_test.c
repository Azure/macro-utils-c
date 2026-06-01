// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_pri_bool_test.h"

/*test will test that the following values are printed as intended:
0
false
1
true
2
-1
0xCCCCCCCC
0xDDDDDDDD*/
int run_mu_pri_bool_tests(void)
{
    int result = 0;

    char temp[100];

    {/*0*/
        int r = snprintf(temp, sizeof(temp), "%" PRI_BOOL "", MU_BOOL_VALUE(0));
        POOR_MANS_ASSERT((r >= 0) && (r < sizeof(temp)));
        POOR_MANS_ASSERT(strcmp("false (0)", temp) == 0);
    }

    {/*false*/
        int r = snprintf(temp, sizeof(temp), "%" PRI_BOOL "", MU_BOOL_VALUE(false));
        POOR_MANS_ASSERT((r >= 0) && (r < sizeof(temp)));
        POOR_MANS_ASSERT(strcmp("false (0)", temp) == 0);
    }

    {/*1*/
        int r = snprintf(temp, sizeof(temp), "%" PRI_BOOL "", MU_BOOL_VALUE(1));
        POOR_MANS_ASSERT((r >= 0) && (r < sizeof(temp)));
        POOR_MANS_ASSERT(strcmp("true (1)", temp) == 0);
    }

    {/*true*/
        int r = snprintf(temp, sizeof(temp), "%" PRI_BOOL "", MU_BOOL_VALUE(true));
        POOR_MANS_ASSERT((r >= 0) && (r < sizeof(temp)));
        POOR_MANS_ASSERT(strcmp("true (1)", temp) == 0);
    }

    {/*2*/
        int r = snprintf(temp, sizeof(temp), "%" PRI_BOOL "", MU_BOOL_VALUE(2));
        POOR_MANS_ASSERT((r >= 0) && (r < sizeof(temp)));
        POOR_MANS_ASSERT(strcmp("true (2)", temp) == 0);
    }

    {/*-1*/
        int r = snprintf(temp, sizeof(temp), "%" PRI_BOOL "", MU_BOOL_VALUE(-1));
        POOR_MANS_ASSERT((r >= 0) && (r < sizeof(temp)));
        POOR_MANS_ASSERT(strcmp("true (-1)", temp) == 0);
    }

    {/*0xCCCCCCCC*/
        int r = snprintf(temp, sizeof(temp), "%" PRI_BOOL "", MU_BOOL_VALUE(0xCCCCCCCC));
        POOR_MANS_ASSERT((r >= 0) && (r < sizeof(temp)));
        POOR_MANS_ASSERT(strcmp("true (-858993460)", temp) == 0);
    }

    {/*0xDDDDDDDD*/
        int r = snprintf(temp, sizeof(temp), "%" PRI_BOOL "", MU_BOOL_VALUE(0xDDDDDDDD));
        POOR_MANS_ASSERT((r >= 0) && (r < sizeof(temp)));
        POOR_MANS_ASSERT(strcmp("true (-572662307)", temp) == 0);
    }

    return result;
}
