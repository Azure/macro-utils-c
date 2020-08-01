#Copyright (c) Microsoft. All rights reserved.

#this is CMakeLists.txt for macro_utils_int_tests
#since every single other project (testrunnerswitcher, ctest, umock_c etc) uses macro_utils
#it means that macro_utils has its own test infrastructure (cannot call into build_c_test_artifacts)

include_directories(${MACRO_UTILS_INC_FOLDER})

set(macro_utils_int_tests_c_files
    define_struct_test.c
    for_each_1_keep_2_test.c
    main.c
    mu_convert_enum_test.c
    mu_count_array_items_test.c
    mu_count_1_or_more_arg_test.c
    mu_define_enum_2_test.c
    mu_define_enum_2_without_invalid_test.c
    mu_define_enum_test.c
    mu_define_local_enum_test.c
    mu_eat_empty_args_test.c
    mu_is_empty_test.c
    mu_has_comma_test.c
    mu_pri_enum_test.c
    mu_the_nth_arg_test.c
)

set(macro_utils_int_tests_h_files
    define_struct_test.h
    for_each_1_keep_2_test.h
    mu_convert_enum_test.h
    mu_count_array_items_test.h
    mu_count_1_or_more_arg_test.h
    mu_define_enum_2_test.h
    mu_define_enum_2_without_invalid_test.h
    mu_define_enum_test.h
    mu_define_local_enum_test.h
    mu_eat_empty_args_test.h
    mu_is_empty_test.h
    mu_has_comma_test.h
    mu_pri_enum_test.h
    mu_the_nth_arg_test.h
    
    test_helper.h
    ${MACRO_UTILS_INC_FOLDER}/azure_macro_utils/macro_utils.h
    ${MACRO_UTILS_INC_FOLDER}/azure_macro_utils/macro_utils_generated.h
)
    
add_executable(macro_utils_int_tests ${macro_utils_int_tests_c_files} ${macro_utils_int_tests_h_files})

add_test(NAME macro_utils_int_tests COMMAND macro_utils_int_tests)
