// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "for_each_1_keep_1_test.h"

// build variables out of a list of 3 elements
#define LIST_3_ELEMENTS \
    41, 42, 43

#define MY_MACRO_X(val, var) \
    static int MU_C2(x_value_1_, var) = val;

MU_FOR_EACH_1_KEEP_1(MY_MACRO_X, 5, LIST_3_ELEMENTS)

// build variables out of a list of 1 element
#define LIST_1_ELEMENT \
    41

#define MY_MACRO_Y(val, var) \
    static int MU_C2(y_value_1_, var) = val;

MU_FOR_EACH_1_KEEP_1(MY_MACRO_Y, 5, LIST_1_ELEMENT)

int run_for_each_1_keep_1_tests(void)
{
    // check that the appropriate value has been placed in each variable
    POOR_MANS_ASSERT(x_value_1_41 == 5);
    POOR_MANS_ASSERT(x_value_1_42 == 5);
    POOR_MANS_ASSERT(x_value_1_43 == 5);

    POOR_MANS_ASSERT(y_value_1_41 == 5);

    return 0;
}
