// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <string.h>
#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_convert_enum_test.h"

// This lists the values in the first enum
#define TEST_CONVERT_FROM_ENUM_VALUES \
    test_from_a, \
    test_from_b = 42, /* Assigning a value to the enum used to fail ..., now fixed */ \
    test_from_c

MU_DEFINE_ENUM(TEST_CONVERT_FROM_ENUM, TEST_CONVERT_FROM_ENUM_VALUES);

#define TEST_CONVERT_TO_ENUM_VALUES \
    test_to_a, \
    test_to_b

MU_DEFINE_ENUM(TEST_CONVERT_TO_ENUM, TEST_CONVERT_TO_ENUM_VALUES);

#define TEST_CONVERT_TO_ANOTHER_ENUM_VALUES \
    test_to_another_a, \
    test_to_another_b

MU_DEFINE_ENUM(TEST_CONVERT_TO_ANOTHER_ENUM, TEST_CONVERT_TO_ANOTHER_ENUM_VALUES);

// The following code should not compile because there is a missing test_from_b in the from values :
/*MU_DEFINE_CONVERT_ENUM(TEST_CONVERT_FROM_ENUM, TEST_CONVERT_TO_ENUM,
    test_from_a, test_to_a,
    test_from_c, test_to_b);*/

// Also the following code should not compile because it uses a from value that is not part of the enum :
/*MU_DEFINE_CONVERT_ENUM(TEST_CONVERT_FROM_ENUM, TEST_CONVERT_TO_ENUM,
    test_from_a, test_to_a,
    42, test_to_a,
    test_from_c, test_to_b);*/

MU_DEFINE_CONVERT_ENUM(TEST_CONVERT_FROM_ENUM, TEST_CONVERT_TO_ENUM,
    test_from_a, test_to_a,
    test_from_b, test_to_b,
    test_from_c, test_to_b);

// This has to compile :-) to prove that we can map the same from enum to 2 different to enums
MU_DEFINE_CONVERT_ENUM(TEST_CONVERT_FROM_ENUM, TEST_CONVERT_TO_ANOTHER_ENUM,
    test_from_a, test_to_another_a,
    test_from_b, test_to_another_b,
    test_from_c, test_to_another_b);

int run_mu_convert_enum_tests(void)
{
    int result = 0;

    TEST_CONVERT_TO_ENUM result_value;
    int convert_result;

    convert_result = MU_CONVERT_ENUM(TEST_CONVERT_FROM_ENUM, TEST_CONVERT_TO_ENUM)(test_from_a, &result_value);
    POOR_MANS_ASSERT(convert_result == 0);
    POOR_MANS_ASSERT(result_value == test_to_a);

    convert_result = MU_CONVERT_ENUM(TEST_CONVERT_FROM_ENUM, TEST_CONVERT_TO_ENUM)(test_from_b, &result_value);
    POOR_MANS_ASSERT(convert_result == 0);
    POOR_MANS_ASSERT(result_value == test_to_b);

    convert_result = MU_CONVERT_ENUM(TEST_CONVERT_FROM_ENUM, TEST_CONVERT_TO_ENUM)(test_from_c, &result_value);
    POOR_MANS_ASSERT(convert_result == 0);
    POOR_MANS_ASSERT(result_value == test_to_b);

    convert_result = MU_CONVERT_ENUM(TEST_CONVERT_FROM_ENUM, TEST_CONVERT_TO_ENUM)(424242, &result_value);
    POOR_MANS_ASSERT(convert_result != 0);

    return result;
}
