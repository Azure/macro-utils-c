#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

#since every single other project (testrunnerswitcher, ctest, umock_c etc) uses macro_utils
#it means that macro_utils has its own test infrastructure (cannot call into build_test_artifacts),
#so build_test_folder cannot be used here. the subfolder below is laid out and named exactly the
#way build_test_folder/build_test_artifacts would have generated it.

if(${run_int_tests})
    add_subdirectory(macro_utils_int)
endif()
