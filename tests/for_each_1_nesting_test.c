// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "for_each_1_nesting_test.h"

// Test that we can nest MU_FOR_EACH_1 by using MU_FOR_EACH_1A

#define NESTED_ITEMS_2 \
    ITEM(INNER_1, INNER_2), \
    ITEM(INNER_3, INNER_4, INNER_5), \
    ITEM(INNER_6)

#define HANDLE_NESTED_ITEMS_2_INNER(x) \
    static const char* MU_C2(var_, x) = MU_TOSTRING(x);

#if defined(_MSC_VER) && (_MSC_VER < 1920 )
#define HANDLE_NESTED_ITEMS_2_ITEM(...) \
    MU_FOR_EACH_1(HANDLE_NESTED_ITEMS_2_INNER, __VA_ARGS__)
#define HANDLE_NESTED_ITEMS_2(item) MU_C2(HANDLE_NESTED_ITEMS_2_, item)
#else
#define HANDLE_NESTED_ITEMS_2_ITEM(...) \
    MU_FOR_EACH_1A(HANDLE_NESTED_ITEMS_2_INNER, __VA_ARGS__)
#define HANDLE_NESTED_ITEMS_2(item) MU_C2A(HANDLE_NESTED_ITEMS_2_, item)
#endif

MU_FOR_EACH_1(HANDLE_NESTED_ITEMS_2, NESTED_ITEMS_2)

// Test that we can nest MU_FOR_EACH_1 twice by using MU_FOR_EACH_1A and MU_FOR_EACH_1B

#define NESTED_ITEMS_3 \
    ITEM(INNER(VALUE_1, VALUE_2), INNER(VALUE_3, VALUE_4, VALUE_5)), \
    ITEM(INNER(VALUE_6), INNER(VALUE_7), INNER(VALUE_8)), \
    ITEM(INNER(VALUE_9, VALUE_10))

#define HANDLE_NESTED_ITEMS_3_VALUE(x) \
    static const char* MU_C2(double_nest_, x) = MU_TOSTRING(x);

#if defined(_MSC_VER) && (_MSC_VER < 1920 )
#define HANDLE_NESTED_ITEMS_3_INNER(...) \
    MU_FOR_EACH_1(HANDLE_NESTED_ITEMS_3_VALUE, __VA_ARGS__)
#define HANDLE_NESTED_ITEMS_3_INNER_PROXY(item) MU_C2(HANDLE_NESTED_ITEMS_3_, item)

#define HANDLE_NESTED_ITEMS_3_ITEM(...) \
    MU_FOR_EACH_1(HANDLE_NESTED_ITEMS_3_INNER_PROXY, __VA_ARGS__)
#define HANDLE_NESTED_ITEMS_3(item) MU_C2(HANDLE_NESTED_ITEMS_3_, item)
#else
#define HANDLE_NESTED_ITEMS_3_INNER(...) \
    MU_FOR_EACH_1B(HANDLE_NESTED_ITEMS_3_VALUE, __VA_ARGS__)
#define HANDLE_NESTED_ITEMS_3_INNER_PROXY(item) MU_C2B(HANDLE_NESTED_ITEMS_3_, item)

#define HANDLE_NESTED_ITEMS_3_ITEM(...) \
    MU_FOR_EACH_1A(HANDLE_NESTED_ITEMS_3_INNER_PROXY, __VA_ARGS__)
#define HANDLE_NESTED_ITEMS_3(item) MU_C2A(HANDLE_NESTED_ITEMS_3_, item)
#endif

MU_FOR_EACH_1(HANDLE_NESTED_ITEMS_3, NESTED_ITEMS_3)

int run_for_each_1_nesting_tests(void)
{
    // check that the appropriate value has been placed in each variable
    POOR_MANS_ASSERT(strcmp(var_INNER_1, "INNER_1") == 0);
    POOR_MANS_ASSERT(strcmp(var_INNER_2, "INNER_2") == 0);
    POOR_MANS_ASSERT(strcmp(var_INNER_3, "INNER_3") == 0);
    POOR_MANS_ASSERT(strcmp(var_INNER_4, "INNER_4") == 0);
    POOR_MANS_ASSERT(strcmp(var_INNER_5, "INNER_5") == 0);
    POOR_MANS_ASSERT(strcmp(var_INNER_6, "INNER_6") == 0);

    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_1, "VALUE_1") == 0);
    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_2, "VALUE_2") == 0);
    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_3, "VALUE_3") == 0);
    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_4, "VALUE_4") == 0);
    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_5, "VALUE_5") == 0);
    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_6, "VALUE_6") == 0);
    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_7, "VALUE_7") == 0);
    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_8, "VALUE_8") == 0);
    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_9, "VALUE_9") == 0);
    POOR_MANS_ASSERT(strcmp(double_nest_VALUE_10, "VALUE_10") == 0);

    return 0;
}
