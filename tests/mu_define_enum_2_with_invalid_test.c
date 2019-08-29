// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#include "azure_macro_utils/macro_utils.h"

#include "mu_define_enum_with_invalid_test.h"

// This lists the values in the enum
#define TEST5_ENUM_VALUES \
    test5_a, 2, \
    test5_b, 42

// This will define an enum that has an INVALID value as first enum value and then it has the enum values
// mentioned in TEST5_ENUM_VALUES
MU_DEFINE_ENUM_2_WITH_INVALID(TEST5_ENUM, TEST5_ENUM_VALUES);

int run_mu_define_enum_2_with_invalid_tests(void)
{
    int result = 0;

    TEST5_ENUM someUnusedVariable; /*but wants to see that the type "TEST5_ENUM" is a real type*/
    (void)someUnusedVariable;

    POOR_MANS_ASSERT(TEST5_ENUM_INVALID == 0);
    POOR_MANS_ASSERT(test5_a == 2);
    POOR_MANS_ASSERT(test5_b == 42);

    return result;
}
