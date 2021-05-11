// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <string.h>
#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_define_enum_test.h"

// This lists the values in the enum
#define TEST4_ENUM_VALUES \
    test4_a, \
    test4_b

// This will define an enum that has an INVALID value as first enum value and then it has the enum values
// mentioned in TEST4_ENUM_VALUES
MU_DEFINE_ENUM(TEST4_ENUM, TEST4_ENUM_VALUES);
MU_DEFINE_ENUM_STRINGS(TEST4_ENUM, TEST4_ENUM_VALUES);

// This lists the values in the enum
#define TEST5_ENUM_VALUES \
    test5_a, \
    test5_b = 42

MU_DEFINE_ENUM(TEST5_ENUM, TEST5_ENUM_VALUES);
MU_DEFINE_ENUM_STRINGS(TEST5_ENUM, TEST5_ENUM_VALUES);

// This enum has a zero after another non-zero value
#define TEST6_ENUM_VALUES \
    test6_a = 42, /* a well known non-zero value */ \
    test6_b = 0, /* a zero value to check this edge case */ \
    test6_c = -1, /* a negative value */ \
    test6_d, /* automagically assigned by the language */ \
    test6_e, /* another one */ \
    test6_f = test6_e, /* one that equals the previous value, just to check that the macros can handle it */ \
    test6_g = test6_f + 1, /* add one with our little hands */ \
    test6_h = (43 + 42), /* have a paranthesis */ \
    test6_i = 5 - 1, /* have a minus */ \
    test6_j = -2 \

MU_DEFINE_ENUM(TEST6_ENUM, TEST6_ENUM_VALUES);
MU_DEFINE_ENUM_STRINGS(TEST6_ENUM, TEST6_ENUM_VALUES);

// An enum without INVALID
#define TEST7_ENUM_VALUES \
    test7_a, \
    test7_b = 42

MU_DEFINE_ENUM_WITHOUT_INVALID(TEST7_ENUM, TEST7_ENUM_VALUES);
MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID(TEST7_ENUM, TEST7_ENUM_VALUES);

int run_mu_define_enum_tests(void)
{
    int result = 0;

    TEST4_ENUM someUnusedVariable; /*but wants to see that the type "TEST4_ENUM" is a real type*/
    (void)someUnusedVariable;

    POOR_MANS_ASSERT(TEST4_ENUM_INVALID == 0);
    POOR_MANS_ASSERT(test4_a == 1);

    const char* TEST4_test4_a = MU_ENUM_TO_STRING(TEST4_ENUM, 1);
    POOR_MANS_ASSERT(TEST4_test4_a != NULL);
    POOR_MANS_ASSERT(strcmp("test4_a", TEST4_test4_a) == 0);

    POOR_MANS_ASSERT(MU_ENUM_VALUE_COUNT(TEST4_ENUM_VALUES) == 3);

    const char* TEST5_test5_b = MU_ENUM_TO_STRING(TEST5_ENUM, 42);
    POOR_MANS_ASSERT(TEST5_test5_b != NULL);
    POOR_MANS_ASSERT(strcmp("test5_b = 42", TEST5_test5_b) == 0);

    const char* TEST5_unknown = MU_ENUM_TO_STRING(TEST5_ENUM, 41);
    POOR_MANS_ASSERT(TEST5_unknown != NULL);
    POOR_MANS_ASSERT(strcmp("NULL", TEST5_unknown) == 0);

    const char* TEST6_test6_a = MU_ENUM_TO_STRING(TEST6_ENUM, test6_a);
    POOR_MANS_ASSERT(TEST6_test6_a != NULL);
    POOR_MANS_ASSERT(strcmp("test6_a = 42", TEST6_test6_a) == 0);

    // test6_b and TEST6_ENUM_INVALID are both 0
    const char* TEST6_test6_b = MU_ENUM_TO_STRING(TEST6_ENUM, test6_b);
    POOR_MANS_ASSERT(TEST6_test6_b != NULL);
    POOR_MANS_ASSERT(strcmp("TEST6_ENUM_INVALID", TEST6_test6_b) == 0);

    const char* TEST6_test6_c = MU_ENUM_TO_STRING(TEST6_ENUM, test6_c);
    POOR_MANS_ASSERT(TEST6_test6_c != NULL);
    POOR_MANS_ASSERT(strcmp("test6_c = -1", TEST6_test6_c) == 0);

    // test6_d and TEST6_ENUM_INVALID are both 0
    const char* TEST6_test6_d = MU_ENUM_TO_STRING(TEST6_ENUM, test6_d);
    POOR_MANS_ASSERT(TEST6_test6_d != NULL);
    POOR_MANS_ASSERT(strcmp("TEST6_ENUM_INVALID", TEST6_test6_d) == 0);

    const char* TEST6_test6_e = MU_ENUM_TO_STRING(TEST6_ENUM, test6_e);
    POOR_MANS_ASSERT(TEST6_test6_e != NULL);
    POOR_MANS_ASSERT(strcmp("test6_e", TEST6_test6_e) == 0);

    // test6_e and test6_f are both the same value
    const char* TEST6_test6_f = MU_ENUM_TO_STRING(TEST6_ENUM, test6_f);
    POOR_MANS_ASSERT(TEST6_test6_f != NULL);
    POOR_MANS_ASSERT(strcmp("test6_e", TEST6_test6_f) == 0);

    const char* TEST6_test6_g = MU_ENUM_TO_STRING(TEST6_ENUM, test6_g);
    POOR_MANS_ASSERT(TEST6_test6_g != NULL);
    POOR_MANS_ASSERT(strcmp("test6_g = test6_f + 1", TEST6_test6_g) == 0);

    const char* TEST6_test6_i = MU_ENUM_TO_STRING(TEST6_ENUM, test6_i);
    POOR_MANS_ASSERT(TEST6_test6_i != NULL);
    POOR_MANS_ASSERT(strcmp("test6_i = 5 - 1", TEST6_test6_i) == 0);

    const char* TEST6_test6_j = MU_ENUM_TO_STRING(TEST6_ENUM, test6_j);
    POOR_MANS_ASSERT(TEST6_test6_j != NULL);
    POOR_MANS_ASSERT(strcmp("test6_j = -2", TEST6_test6_j) == 0);

    POOR_MANS_ASSERT(MU_ENUM_VALUE_COUNT_WITHOUT_INVALID(TEST7_ENUM_VALUES) == 2);

    const char* TEST7_test7_a = MU_ENUM_TO_STRING(TEST7_ENUM, 0);
    POOR_MANS_ASSERT(TEST7_test7_a != NULL);
    POOR_MANS_ASSERT(strcmp("test7_a", TEST7_test7_a) == 0);

    const char* TEST7_test7_b = MU_ENUM_TO_STRING(TEST7_ENUM, 42);
    POOR_MANS_ASSERT(TEST7_test7_b != NULL);
    POOR_MANS_ASSERT(strcmp("test7_b = 42", TEST7_test7_b) == 0);

    return result;
}
