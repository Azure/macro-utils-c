// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <string.h>
#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_convert_enum_with_default_test.h"

// This lists the values in the first enum
#define TEST_CONVERT_WITH_DEFAULT_FROM_ENUM_VALUES \
    test_from_a, \
    test_from_b = 42, /* Assigning a value to the enum used to fail ..., now fixed */ \
    test_from_c

MU_DEFINE_ENUM(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_FROM_ENUM_VALUES);
MU_DEFINE_ENUM_STRINGS(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_FROM_ENUM_VALUES);

#define TEST_CONVERT_WITH_DEFAULT_TO_ENUM_VALUES \
    test_to_a, \
    test_to_b

MU_DEFINE_ENUM(TEST_CONVERT_WITH_DEFAULT_TO_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ENUM_VALUES);
MU_DEFINE_ENUM_STRINGS(TEST_CONVERT_WITH_DEFAULT_TO_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ENUM_VALUES);

#define TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM_VALUES \
    test_to_another_a, \
    test_to_another_b, \
    test_to_another_default

MU_DEFINE_ENUM(TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM_VALUES);
MU_DEFINE_ENUM_STRINGS(TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM_VALUES);

MU_DEFINE_CONVERT_ENUM_WITH_DEFAULT(printf, TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ENUM, test_to_b,
    test_from_a, test_to_a,
    test_from_b, test_to_b,
    test_from_c, test_to_b);

MU_DEFINE_CONVERT_ENUM_WITH_DEFAULT_WITHOUT_INVALID(printf, TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM, test_to_another_default,
    test_from_a, test_to_another_a,
    test_from_b, test_to_another_b,
    test_from_c, test_to_another_b);

int run_mu_convert_enum_with_default_tests(void)
{
    int result = 0;

    TEST_CONVERT_WITH_DEFAULT_TO_ENUM result_value;

    result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ENUM)(test_from_a);
    POOR_MANS_ASSERT(result_value == test_to_a);

    result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ENUM)(test_from_b);
    POOR_MANS_ASSERT(result_value == test_to_b);

    result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ENUM)(test_from_c);
    POOR_MANS_ASSERT(result_value == test_to_b);

    result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ENUM)(424242);
    POOR_MANS_ASSERT(result_value == test_to_b); // default

    result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ENUM)(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM_INVALID);
    POOR_MANS_ASSERT(result_value == TEST_CONVERT_WITH_DEFAULT_TO_ENUM_INVALID);

    TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM another_result_value;

    another_result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM)(test_from_a);
    POOR_MANS_ASSERT(another_result_value == test_to_another_a);

    another_result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM)(test_from_b);
    POOR_MANS_ASSERT(another_result_value == test_to_another_b);

    another_result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM)(test_from_c);
    POOR_MANS_ASSERT(another_result_value == test_to_another_b);

    another_result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM)(424242);
    POOR_MANS_ASSERT(another_result_value == test_to_another_default);

    another_result_value = MU_CONVERT_ENUM_WITH_DEFAULT(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM, TEST_CONVERT_WITH_DEFAULT_TO_ANOTHER_ENUM)(TEST_CONVERT_WITH_DEFAULT_FROM_ENUM_INVALID);
    POOR_MANS_ASSERT(another_result_value == test_to_another_default);

    return result;
}
