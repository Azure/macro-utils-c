// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>

#include "test_helper.h"

#include "define_struct_test.h"
#include "for_each_1_keep_2_test.h"
#include "mu_convert_enum_test.h"
#include "mu_count_array_items_test.h"
#include "mu_count_arg_test.h"
#include "mu_count_1_or_more_arg_test.h"
#include "mu_define_enum_2_test.h"
#include "mu_define_enum_2_without_invalid_test.h"
#include "mu_define_enum_test.h"
#include "mu_define_local_enum_test.h"
#include "mu_eat_empty_args_test.h"
#include "mu_is_empty_test.h"
#include "mu_has_comma_test.h"
#include "mu_pri_enum_test.h"
#include "mu_the_nth_arg_test.h"
#include "mu_expand_no_expand_test.h"
#include "mu_for_each_1_paste_test.h"

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

    result = run_mu_define_enum_2_without_invalid_test();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_mu_define_enum_2_without_invalid_test();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_mu_eat_empty_args_test();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_define_struct_tests();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_for_each_1_keep_2_tests();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_mu_count_array_items_tests();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_mu_define_enum_tests();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_mu_convert_enum_tests();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_mu_define_local_enum_tests();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_mu_define_enum_2_tests();
    POOR_MANS_ASSERT(result == 0);
    
    result = run_mu_pri_enum_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_expand_no_expand_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_for_each_1_paste_test();
    POOR_MANS_ASSERT(result == 0);
    
    return 0;
}

