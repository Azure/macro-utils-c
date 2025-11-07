#Copyright (c) Microsoft. All rights reserved.

#this is CMakeLists.txt for macro_utils_int_tests
#since every single other project (testrunnerswitcher, ctest, umock_c etc) uses macro_utils
#it means that macro_utils has its own test infrastructure (cannot call into build_c_test_artifacts)

set(macro_utils_int_tests_c_files
    define_struct_test.c
    for_each_1_keep_1_test.c
    for_each_1_keep_2_test.c
    for_each_1_keep_1_counted_test.c
    for_each_1_keep_2_counted_test.c
    for_each_1_nesting_test.c
    main.c
    mu_convert_enum_test.c
    mu_convert_enum_with_default_test.c
    mu_count_arg_test.c
    mu_count_array_items_test.c
    mu_count_1_or_more_arg_test.c
    mu_define_enum_test.c
    mu_define_local_enum_test.c
    mu_different_test.c
    mu_eat_empty_args_test.c
    mu_is_empty_test.c
    mu_pri_bool_test.c
    mu_pri_enum_test.c
    mu_pri_time_t_test.c
    mu_the_nth_arg_test.c
    mu_expand_no_expand_test.c
    mu_for_each_1_paste_test.c
    mu_tostring_test.c
    static_assert_test.c
    pri_kb_test.c
)

set(macro_utils_int_tests_h_files
    define_struct_test.h
    for_each_1_keep_1_test.h
    for_each_1_keep_2_test.h
    for_each_1_keep_1_counted_test.h
    for_each_1_keep_2_counted_test.h
    for_each_1_nesting_test.h
    mu_convert_enum_test.h
    mu_convert_enum_with_default_test.h
    mu_count_arg_test.h
    mu_count_array_items_test.h
    mu_count_1_or_more_arg_test.h
    mu_define_enum_test.h
    mu_define_local_enum_test.h
    mu_different_test.h
    mu_eat_empty_args_test.h
    mu_is_empty_test.h
    mu_pri_bool_test.h
    mu_pri_enum_test.h
    mu_pri_time_t_test.h
    mu_the_nth_arg_test.h
    mu_expand_no_expand_test.h
    mu_for_each_1_paste_test.h
    mu_tostring_test.h
    static_assert_test.h
    pri_kb_test.h

    test_helper.h
)

add_executable(macro_utils_int_tests ${macro_utils_int_tests_c_files} ${macro_utils_int_tests_h_files})
target_link_libraries(macro_utils_int_tests macro_utils_c)

add_test(NAME macro_utils_int_tests COMMAND macro_utils_int_tests)
