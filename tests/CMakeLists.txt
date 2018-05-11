#Copyright (c) Microsoft. All rights reserved.

#this is CMakeLists.txt for macro_utils_int_tests
#since every single other project (testrunnerswitcher, ctest, umock_c etc) uses macro_utils
#it means that macro_utils has its own test infrastructure (cannot call into build_c_test_artifacts)

include_directories(${MACRO_UTILS_INC_FOLDER})

add_executable(macro_utils_int_tests macro_utils_int_tests.c define_enum_2_test.c define_enum_2_test.h)


add_test(NAME macro_utils_int_tests COMMAND macro_utils_int_tests)