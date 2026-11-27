// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <cstdio>
#include <cstring>

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_define_enum_class_strings_test.h"

namespace test_namespace
{
    enum class test9_enum_class
    {
        test9_a = 5,
        test9_b = -1,
        test9_c = 100,
        test9_d = 7
    };

    enum class test10_enum_class
    {
        test10_a,
        test10_b = test10_a,
        test10_c
    };
}

using TEST9_ENUM_CLASS = test_namespace::test9_enum_class;
using TEST10_ENUM_CLASS = test_namespace::test10_enum_class;

// test9_d is not in the list
#define TEST9_ENUM_CLASS_VALUES \
    test9_a, \
    test9_b, \
    test9_c

MU_DEFINE_ENUM_CLASS_STRINGS(TEST9_ENUM_CLASS, TEST9_ENUM_CLASS_VALUES)

// test10_b has the same value as test10_a and is listed first
#define TEST10_ENUM_CLASS_VALUES \
    test10_b, \
    test10_a, \
    test10_c

MU_DEFINE_ENUM_CLASS_STRINGS(TEST10_ENUM_CLASS, TEST10_ENUM_CLASS_VALUES)

int run_mu_define_enum_class_strings_tests(void)
{
    const char* TEST9_test9_a = MU_ENUM_TO_STRING(TEST9_ENUM_CLASS, TEST9_ENUM_CLASS::test9_a);
    POOR_MANS_ASSERT(TEST9_test9_a != NULL);
    POOR_MANS_ASSERT(strcmp("test9_a", TEST9_test9_a) == 0);

    const char* TEST9_test9_b = MU_ENUM_TO_STRING(TEST9_ENUM_CLASS, TEST9_ENUM_CLASS::test9_b);
    POOR_MANS_ASSERT(TEST9_test9_b != NULL);
    POOR_MANS_ASSERT(strcmp("test9_b", TEST9_test9_b) == 0);

    const char* TEST9_test9_c = MU_ENUM_TO_STRING(TEST9_ENUM_CLASS, TEST9_ENUM_CLASS::test9_c);
    POOR_MANS_ASSERT(TEST9_test9_c != NULL);
    POOR_MANS_ASSERT(strcmp("test9_c", TEST9_test9_c) == 0);

    const char* TEST9_test9_d = MU_ENUM_TO_STRING(TEST9_ENUM_CLASS, TEST9_ENUM_CLASS::test9_d);
    POOR_MANS_ASSERT(TEST9_test9_d != NULL);
    POOR_MANS_ASSERT(strcmp("UNKNOWN", TEST9_test9_d) == 0);

    // the first listed name is returned for values that have more than one name
    const char* TEST10_test10_a = MU_ENUM_TO_STRING(TEST10_ENUM_CLASS, TEST10_ENUM_CLASS::test10_a);
    POOR_MANS_ASSERT(TEST10_test10_a != NULL);
    POOR_MANS_ASSERT(strcmp("test10_b", TEST10_test10_a) == 0);

    char TEST9_test9_b_formatted[32];
    (void)snprintf(TEST9_test9_b_formatted, sizeof(TEST9_test9_b_formatted), "%" PRI_MU_ENUM, MU_ENUM_VALUE(TEST9_ENUM_CLASS, TEST9_ENUM_CLASS::test9_b));
    POOR_MANS_ASSERT(strcmp("test9_b (-1)", TEST9_test9_b_formatted) == 0);

    return 0;
}
