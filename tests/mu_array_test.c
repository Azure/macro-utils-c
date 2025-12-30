// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#define MU_ARRAY_MAX_COUNT 5 /*can be overridden before including macro_utils.h*/
#include "macro_utils/macro_utils.h"

#include "mu_array_test.h"

MU_STATIC_ASSERT(MU_ARRAY_MAX_COUNT >= 3); /*this test needs at least 3 elements printing capability*/

#define INVENT_NAME(index, ... ) MU_TOSTRING(index) "escu" , /*this results in "zeroescu", "unuescu", "doiescu" etc... Joking: 0escu, 1escu, 2escu*/

static const char* names_1[] = { "Ionescu" };
static const char* names_2[] = { "Popescu", "Ionescu" };
static const char* names_3[] = { "Georgescu", "Popescu", "Ionescu" };
static const char* names_more_than_MU_ARRAY_MAX_COUNT[] = { MU_DO_ASC(MU_DEC(MU_ARRAY_MAX_COUNT), INVENT_NAME) "Ixulescu", "Igreculescu"}; /*Ixulescu, Igreculescu exceeds the printing limit for ARRAY_ELEMENT_VALUE*/

int run_mu_array_tests(void)
{
    char temp[1000]; /*sufficient to hold all the names representations*/
    int result;

    /*checking that PRI_ARRAY_ELEMENT and ARRAY_ELEMENT_VALUE work for a very regular element(s)*/

    /*array of 0 element*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_1, 0 /*hard coded array size of 0*/, 0));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "") == 0);

    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_1, 0 /*hard coded array size of 0*/, 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "") == 0);

    /*array of 1 element*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_1, sizeof(names_1)/sizeof(names_1[0]), 0));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "[0]=Ionescu") == 0);

    /*index "1" is out of bounds for an array with 1 elements - no printing with , ...*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_1, sizeof(names_1) / sizeof(names_1[0]), 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "") == 0);

    /*index "2" is out of bounds for an array with 1 elements - no printing with , ...*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_1, sizeof(names_1) / sizeof(names_1[0]), 2));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "") == 0);

    /*array of 2 element*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_2, sizeof(names_2) / sizeof(names_2[0]), 0));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "[0]=Popescu") == 0);

    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_2, sizeof(names_2) / sizeof(names_2[0]), 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, ", [1]=Ionescu") == 0);

    /*index "2" is out of bounds for an array with 2 elements - no printing with , ...*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_2, sizeof(names_2) / sizeof(names_2[0]), 2));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "") == 0);

    /*index "3 is out of bounds for an array with 2 elements - no printing with , ...*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_2, sizeof(names_2) / sizeof(names_2[0]), 2));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "") == 0);

    /*array of 3 element*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_3, sizeof(names_3) / sizeof(names_3[0]), 0));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "[0]=Georgescu") == 0);

    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_3, sizeof(names_3) / sizeof(names_3[0]), 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, ", [1]=Popescu") == 0);

    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_3, sizeof(names_3) / sizeof(names_3[0]), 2));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, ", [2]=Ionescu") == 0);

    /*index "3 is out of bounds for an array with 3elements - no printing with ,...*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_3, sizeof(names_3) / sizeof(names_3[0]), 3));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "") == 0);

    /*when the [i]= part is not available (because MU_ARRAY_INDEX_AS_STRING is not build that much), this should expand to "..." to explain that some printing limit was exceeded*/

    /*array of MU_ARRAY_MAX_COUNT+2 elements... which exceeds #define MU_ARRAY_MAX_COUNT*/
    int array_size = sizeof(names_more_than_MU_ARRAY_MAX_COUNT) / sizeof(names_more_than_MU_ARRAY_MAX_COUNT[0]);
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_more_than_MU_ARRAY_MAX_COUNT, array_size, 0));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "[0]=0escu") == 0);

    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_more_than_MU_ARRAY_MAX_COUNT, array_size, 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, ", [1]=1escu") == 0);

    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_more_than_MU_ARRAY_MAX_COUNT, array_size, 2));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, ", [2]=2escu") == 0);

    /*the MU_ARRAY_MAX_COUNT index here cannot be printed because we don't have the "[3]=" string, so ", ..." is used instead*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_more_than_MU_ARRAY_MAX_COUNT, array_size, MU_ARRAY_MAX_COUNT));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, ", ...") == 0);

    /*the 4th index cannot be printed because it is past the configured size (3)*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_ELEMENT("s") "", ARRAY_ELEMENT_VALUE(names_more_than_MU_ARRAY_MAX_COUNT, array_size, MU_ARRAY_MAX_COUNT+1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "") == 0);

    /*tests for PRI_ARRAY/ARRAY_VALUES*/

    /*array of size 0*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY("s") "", ARRAY_VALUES(names_1, 0)); /*array size is harcoded 0*/
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{  }") == 0);

    /*array of size 0*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY("s") "", ARRAY_VALUES(names_1, sizeof(names_1) / sizeof(names_1[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Ionescu }") == 0);

    /*array of size 2*/
    /*printing all the array*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY("s") "", ARRAY_VALUES(names_2, sizeof(names_2) / sizeof(names_2[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu, [1]=Ionescu }") == 0);

    /*printing just the first name*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY("s") "", ARRAY_VALUES(names_2, 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu }") == 0);

    /*array of size 3*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY("s") "", ARRAY_VALUES(names_3, sizeof(names_3) / sizeof(names_3[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Georgescu, [1]=Popescu, [2]=Ionescu }") == 0);

    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY("s") "", ARRAY_VALUES(names_more_than_MU_ARRAY_MAX_COUNT, sizeof(names_more_than_MU_ARRAY_MAX_COUNT) / sizeof(names_more_than_MU_ARRAY_MAX_COUNT[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));

    char expected_result[1000] = "{ ";
    for (int i = 0; i < MU_ARRAY_MAX_COUNT; i++)
    {
        if (i > 0)
        {
            (void)strcat(expected_result, ", ");
        }
        char compound[20];
        (void)snprintf(compound, sizeof(compound), "[%d]=%descu", i, i);
        (void)strcat(expected_result, compound);
    }
    (void)strcat(expected_result, ", ... }");
    POOR_MANS_ASSERT(strcmp(temp, expected_result) == 0);

    return 0;
}
