// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include <stdlib.h>

#ifdef USE_VLD
#error USE_VLD is defined
#endif

#include "test_helper.h"

#include "define_struct_test.h"
#include "for_each_1_keep_1_test.h"
#include "for_each_1_keep_2_test.h"
#include "for_each_1_keep_1_counted_test.h"
#include "for_each_1_keep_2_counted_test.h"
#include "for_each_1_nesting_test.h"
#include "mu_convert_enum_test.h"
#include "mu_convert_enum_with_default_test.h"
#include "mu_count_array_items_test.h"
#include "mu_count_arg_test.h"
#include "mu_count_1_or_more_arg_test.h"
#include "mu_define_enum_test.h"
#include "mu_different_test.h"
#include "mu_define_local_enum_test.h"
#include "mu_eat_empty_args_test.h"
#include "mu_is_empty_test.h"
#include "mu_has_comma_test.h"
#include "mu_pri_enum_test.h"
#include "mu_the_nth_arg_test.h"
#include "mu_expand_no_expand_test.h"
#include "mu_for_each_1_paste_test.h"
#include "mu_pri_bool_test.h"
#include "mu_pri_time_t_test.h"
#include "mu_tostring_test.h"
#include "static_assert_test.h"
#include "pri_kb_test.h"

int main(void)
{
    int result;

    result = run_mu_the_nth_arg_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_count_1_or_more_arg_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_has_comma_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_is_empty_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_count_arg_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_eat_empty_args_test();
    POOR_MANS_ASSERT(result == 0);

    result = run_define_struct_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_for_each_1_keep_1_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_for_each_1_keep_2_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_for_each_1_keep_1_counted_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_for_each_1_keep_2_counted_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_for_each_1_nesting_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_count_array_items_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_define_enum_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_convert_enum_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_convert_enum_with_default_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_define_local_enum_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_pri_enum_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_expand_no_expand_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_for_each_1_paste_test();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_pri_bool_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_pri_time_t_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_different_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_tostring_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_static_assert_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_pri_kb_tests();
    POOR_MANS_ASSERT(result == 0);

    (void)malloc(3);

    return 0;
}

