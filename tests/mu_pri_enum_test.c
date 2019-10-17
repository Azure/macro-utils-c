// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include "test_helper.h"

#include "azure_macro_utils/macro_utils.h"

#include "mu_pri_enum_test.h"

/*this file consist of 2 tests - one test will verify an enum(TEST_PRI_ENUM) introduced by MU_DEFINE_ENUM, the other test will verify an enum introduced by MU_DEFINE_ENUM_2(TEST_PRI_ENUM_2)*/

#define TEST_PRI_ENUM_VALUES    \
    A,                          \
    BC

MU_DEFINE_ENUM(TEST_PRI_ENUM, TEST_PRI_ENUM_VALUES);
MU_DEFINE_ENUM_STRINGS(TEST_PRI_ENUM, TEST_PRI_ENUM_VALUES);

static int verifyMU_ENUM_VALUE_A(const char* empty, const char* valueAsString, int valueAsInt)
{
    POOR_MANS_ASSERT(empty != NULL);
    POOR_MANS_ASSERT(empty[0] == '\0');
    POOR_MANS_ASSERT(valueAsString != NULL);
    POOR_MANS_ASSERT(valueAsString[0] == 'A');
    POOR_MANS_ASSERT(valueAsString[1] == '\0');
    POOR_MANS_ASSERT(valueAsInt == A);
    return 0;
}

static int verifyMU_ENUM_VALUE_BC(const char* empty, const char* valueAsString, int valueAsInt)
{
    POOR_MANS_ASSERT(empty != NULL);
    POOR_MANS_ASSERT(empty[0] == '\0');
    POOR_MANS_ASSERT(valueAsString != NULL);
    POOR_MANS_ASSERT(valueAsString[0] == 'B');
    POOR_MANS_ASSERT(valueAsString[1] == 'C');
    POOR_MANS_ASSERT(valueAsString[2] == '\0');
    POOR_MANS_ASSERT(valueAsInt == BC);
    return 0;
}

static int verifyMU_ENUM_VALUE_BC_plus_1(const char* empty, const char* valueAsString, int valueAsInt)
{
    POOR_MANS_ASSERT(empty != NULL);
    POOR_MANS_ASSERT(empty[0] == '\0');
    POOR_MANS_ASSERT(valueAsString != NULL);
    POOR_MANS_ASSERT(valueAsString[0] == 'N');
    POOR_MANS_ASSERT(valueAsString[1] == 'U');
    POOR_MANS_ASSERT(valueAsString[2] == 'L');
    POOR_MANS_ASSERT(valueAsString[3] == 'L');
    POOR_MANS_ASSERT(valueAsString[4] == '\0');
    POOR_MANS_ASSERT(valueAsInt == (int)BC + 1);
    return 0;
}

#define TEST_PRI_ENUM_2_VALUES    \
    X2, 2,                        \
    ZY2, 6

MU_DEFINE_ENUM_2(TEST_PRI_ENUM_2, TEST_PRI_ENUM_2_VALUES);
MU_DEFINE_ENUM_STRINGS_2(TEST_PRI_ENUM_2, TEST_PRI_ENUM_2_VALUES);

static int verifyMU_ENUM_VALUE_X2(const char* empty, const char* valueAsString, int valueAsInt)
{
    POOR_MANS_ASSERT(empty != NULL);
    POOR_MANS_ASSERT(empty[0] == '\0');
    POOR_MANS_ASSERT(valueAsString != NULL);
    POOR_MANS_ASSERT(valueAsString[0] == 'X');
    POOR_MANS_ASSERT(valueAsString[1] == '2');
    POOR_MANS_ASSERT(valueAsString[2] == '\0');
    POOR_MANS_ASSERT(valueAsInt == X2);
    return 0;
}

static int verifyMU_ENUM_VALUE_ZY2(const char* empty, const char* valueAsString, int valueAsInt)
{
    POOR_MANS_ASSERT(empty != NULL);
    POOR_MANS_ASSERT(empty[0] == '\0');
    POOR_MANS_ASSERT(valueAsString != NULL);
    POOR_MANS_ASSERT(valueAsString[0] == 'Z');
    POOR_MANS_ASSERT(valueAsString[1] == 'Y');
    POOR_MANS_ASSERT(valueAsString[2] == '2');
    POOR_MANS_ASSERT(valueAsString[3] == '\0');
    POOR_MANS_ASSERT(valueAsInt == ZY2);
    return 0;
}

static int verifyMU_ENUM_VALUE_1(const char* empty, const char* valueAsString, int valueAsInt)
{
    POOR_MANS_ASSERT(empty != NULL);
    POOR_MANS_ASSERT(empty[0] == '\0');
    POOR_MANS_ASSERT(valueAsString != NULL);
    POOR_MANS_ASSERT(valueAsString[0] == 'N');
    POOR_MANS_ASSERT(valueAsString[1] == 'U');
    POOR_MANS_ASSERT(valueAsString[2] == 'L');
    POOR_MANS_ASSERT(valueAsString[3] == 'L');
    POOR_MANS_ASSERT(valueAsString[4] == '\0');
    POOR_MANS_ASSERT(valueAsInt == 1);
    return 0;
}

static int verifyMU_ENUM_VALUE_3(const char* empty, const char* valueAsString, int valueAsInt)
{
    POOR_MANS_ASSERT(empty != NULL);
    POOR_MANS_ASSERT(empty[0] == '\0');
    POOR_MANS_ASSERT(valueAsString != NULL);
    POOR_MANS_ASSERT(valueAsString[0] == 'N');
    POOR_MANS_ASSERT(valueAsString[1] == 'U');
    POOR_MANS_ASSERT(valueAsString[2] == 'L');
    POOR_MANS_ASSERT(valueAsString[3] == 'L');
    POOR_MANS_ASSERT(valueAsString[4] == '\0');
    POOR_MANS_ASSERT(valueAsInt == 3);
    return 0;
}

static int verifyMU_ENUM_VALUE_7(const char* empty, const char* valueAsString, int valueAsInt)
{
    POOR_MANS_ASSERT(empty != NULL);
    POOR_MANS_ASSERT(empty[0] == '\0');
    POOR_MANS_ASSERT(valueAsString != NULL);
    POOR_MANS_ASSERT(valueAsString[0] == 'N');
    POOR_MANS_ASSERT(valueAsString[1] == 'U');
    POOR_MANS_ASSERT(valueAsString[2] == 'L');
    POOR_MANS_ASSERT(valueAsString[3] == 'L');
    POOR_MANS_ASSERT(valueAsString[4] == '\0');
    POOR_MANS_ASSERT(valueAsInt == 7);
    return 0;
}

int run_mu_pri_enum_tests(void)
{
    /*test that MU_ENUM_VALUE is "",someString,someInt*/
    POOR_MANS_ASSERT(verifyMU_ENUM_VALUE_A(MU_ENUM_VALUE(TEST_PRI_ENUM, A)) == 0);
    POOR_MANS_ASSERT(verifyMU_ENUM_VALUE_BC(MU_ENUM_VALUE(TEST_PRI_ENUM, BC)) == 0);
    POOR_MANS_ASSERT(verifyMU_ENUM_VALUE_BC_plus_1(MU_ENUM_VALUE(TEST_PRI_ENUM, (TEST_PRI_ENUM)(BC+1))) == 0);

    /*test that MU_PRI_ENUM and MU_ENUM_VALUE work together in printf*/
    (void)printf("%" MU_PRI_ENUM "\n", MU_ENUM_VALUE(TEST_PRI_ENUM, A));

    /*test that MU_ENUM_VALUE is "",someString,someInt*/
    POOR_MANS_ASSERT(verifyMU_ENUM_VALUE_X2(MU_ENUM_VALUE_2(TEST_PRI_ENUM_2, X2)) == 0);
    POOR_MANS_ASSERT(verifyMU_ENUM_VALUE_ZY2(MU_ENUM_VALUE_2(TEST_PRI_ENUM_2, ZY2)) == 0);
    POOR_MANS_ASSERT(verifyMU_ENUM_VALUE_1(MU_ENUM_VALUE_2(TEST_PRI_ENUM_2, (TEST_PRI_ENUM_2)(1))) == 0);
    POOR_MANS_ASSERT(verifyMU_ENUM_VALUE_3(MU_ENUM_VALUE_2(TEST_PRI_ENUM_2, (TEST_PRI_ENUM_2)(3))) == 0);
    POOR_MANS_ASSERT(verifyMU_ENUM_VALUE_7(MU_ENUM_VALUE_2(TEST_PRI_ENUM_2, (TEST_PRI_ENUM_2)(7))) == 0);

    /*test that MU_PRI_ENUM and MU_ENUM_VALUE work together in printf*/
    (void)printf("%" MU_PRI_ENUM "\n", MU_ENUM_VALUE_2(TEST_PRI_ENUM_2, ZY2));

    return 0;
}
