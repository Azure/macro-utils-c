// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <cstdio>
#include <cstring>

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_define_enum_class_strings_test.h"

namespace test_namespace
{
    enum class test_enum_class
    {
        test_a = 5,
        test_b = -1,
        test_c = 100,
        test_d = 7
    };

    enum class test_enum_class_2
    {
        test2_a,
        test2_b = test2_a,
        test2_c
    };
}

using TEST_ENUM_CLASS = test_namespace::test_enum_class;
using TEST_ENUM_CLASS_2 = test_namespace::test_enum_class_2;

// test_d is not in the list
#define TEST_ENUM_CLASS_VALUES \
    test_a, \
    test_b, \
    test_c

MU_DEFINE_ENUM_CLASS_STRINGS(TEST_ENUM_CLASS, TEST_ENUM_CLASS_VALUES)

// test2_b has the same value as test2_a and is listed first
#define TEST_ENUM_CLASS_2_VALUES \
    test2_b, \
    test2_a, \
    test2_c

MU_DEFINE_ENUM_CLASS_STRINGS(TEST_ENUM_CLASS_2, TEST_ENUM_CLASS_2_VALUES)

int run_mu_define_enum_class_strings_tests(void)
{
    const char* TEST_ENUM_CLASS_test_a = MU_ENUM_TO_STRING(TEST_ENUM_CLASS, TEST_ENUM_CLASS::test_a);
    POOR_MANS_ASSERT(TEST_ENUM_CLASS_test_a != NULL);
    POOR_MANS_ASSERT(strcmp("test_a", TEST_ENUM_CLASS_test_a) == 0);

    const char* TEST_ENUM_CLASS_test_b = MU_ENUM_TO_STRING(TEST_ENUM_CLASS, TEST_ENUM_CLASS::test_b);
    POOR_MANS_ASSERT(TEST_ENUM_CLASS_test_b != NULL);
    POOR_MANS_ASSERT(strcmp("test_b", TEST_ENUM_CLASS_test_b) == 0);

    const char* TEST_ENUM_CLASS_test_c = MU_ENUM_TO_STRING(TEST_ENUM_CLASS, TEST_ENUM_CLASS::test_c);
    POOR_MANS_ASSERT(TEST_ENUM_CLASS_test_c != NULL);
    POOR_MANS_ASSERT(strcmp("test_c", TEST_ENUM_CLASS_test_c) == 0);

    const char* TEST_ENUM_CLASS_test_d = MU_ENUM_TO_STRING(TEST_ENUM_CLASS, TEST_ENUM_CLASS::test_d);
    POOR_MANS_ASSERT(TEST_ENUM_CLASS_test_d != NULL);
    POOR_MANS_ASSERT(strcmp("UNKNOWN", TEST_ENUM_CLASS_test_d) == 0);

    // the first listed name is returned for values that have more than one name
    const char* TEST_ENUM_CLASS_2_test2_a = MU_ENUM_TO_STRING(TEST_ENUM_CLASS_2, TEST_ENUM_CLASS_2::test2_a);
    POOR_MANS_ASSERT(TEST_ENUM_CLASS_2_test2_a != NULL);
    POOR_MANS_ASSERT(strcmp("test2_b", TEST_ENUM_CLASS_2_test2_a) == 0);

    char TEST_ENUM_CLASS_test_b_formatted[32];
    (void)snprintf(TEST_ENUM_CLASS_test_b_formatted, sizeof(TEST_ENUM_CLASS_test_b_formatted), "%" PRI_MU_ENUM, MU_ENUM_VALUE(TEST_ENUM_CLASS, TEST_ENUM_CLASS::test_b));
    POOR_MANS_ASSERT(strcmp("test_b (-1)", TEST_ENUM_CLASS_test_b_formatted) == 0);

    return 0;
}
