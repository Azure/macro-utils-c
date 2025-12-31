// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_array_test.h"

static const char* names_1[] = { "Ionescu" };
static const char* names_2[] = { "Popescu", "Ionescu" };
static const char* names_3[] = { "Georgescu", "Popescu", "Ionescu" };

static const wchar_t* wnames_1[] = { L"Ionescu" };
static const wchar_t* wnames_2[] = { L"Popescu", L"Ionescu" };
static const wchar_t* wnames_3[] = { L"Georgescu", L"Popescu", L"Ionescu" };

static int run_mu_array_wstring_tests(void)
{
    char temp[1000]; /*sufficient to hold all the names representations*/
    int result;

    /*tests for PRI_ARRAY/ARRAY_VALUES*/

    /*array of size 0*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_WS "", ARRAY_WS_VALUES(wnames_1, 0)); /*array size is harcoded 0*/
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{  }") == 0);

    /*array of size 1*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_WS "", ARRAY_WS_VALUES(wnames_1, sizeof(wnames_1) / sizeof(wnames_1[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Ionescu }") == 0);

    /*array of size 2*/
    /*printing all the array*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_WS "", ARRAY_WS_VALUES(wnames_2, sizeof(wnames_2) / sizeof(wnames_2[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu, [1]=Ionescu }") == 0);

    /*printing just the first name*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_WS "", ARRAY_WS_VALUES(wnames_2, 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu }") == 0);

    /*array of size 3*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_WS "", ARRAY_WS_VALUES(wnames_3, sizeof(wnames_3) / sizeof(wnames_3[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Georgescu, [1]=Popescu, [2]=Ionescu }") == 0);

    return 0;
}


static int run_mu_array_string_tests(void)
{
    int result;

    result = run_mu_array_wstring_tests();
    POOR_MANS_ASSERT(result == 0);

    char temp[1000]; /*sufficient to hold all the names representations*/

    /*array of size 0*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_S "", ARRAY_S_VALUES(names_1, 0)); /*array size is harcoded 0*/
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{  }") == 0);

    /*array of size 0*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_S "", ARRAY_S_VALUES(names_1, sizeof(names_1) / sizeof(names_1[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Ionescu }") == 0);

    /*array of size 2*/
    /*printing all the array*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_S "", ARRAY_S_VALUES(names_2, sizeof(names_2) / sizeof(names_2[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu, [1]=Ionescu }") == 0);

    /*printing just the first name*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_S "", ARRAY_S_VALUES(names_2, 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu }") == 0);

    /*array of size 3*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_S "", ARRAY_S_VALUES(names_3, sizeof(names_3) / sizeof(names_3[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Georgescu, [1]=Popescu, [2]=Ionescu }") == 0);

    return 0;
}

int run_mu_array_tests(void)
{
    int result;
    result = run_mu_array_string_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_array_wstring_tests();
    POOR_MANS_ASSERT(result == 0);

    return 0;
}
