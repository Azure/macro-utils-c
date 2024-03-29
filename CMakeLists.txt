#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

if(NOT DEFINED CMAKE_MINIMUM_REQUIRED_VERSION)
    cmake_minimum_required(VERSION 3.18)
endif()

# canon way of macro-utils-c from another repo is below. It assumes the using repo has placed macro-utils-c in "deps"

#if ((NOT TARGET macro_utils_c) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/macro-utils-c/CMakeLists.txt))
#    add_subdirectory(deps/macro-utils-c)
#    include_directories(${MACRO_UTILS_INC_FOLDER})
#endif() 

if(TARGET macro_utils_c)
    return()
endif()
    
project(macro_utils_c)

set(MACRO_UTILS_C_VERSION 1.1.0)

option(run_int_tests "set run_int_tests to ON to run int tests (default is OFF)" OFF)

#bring in dependencies
#do not add or build any tests of the dependencies
set(original_run_e2e_tests ${run_e2e_tests})
set(original_run_int_tests ${run_int_tests})
set(original_run_perf_tests ${run_perf_tests})
set(original_run_unittests ${run_unittests})
set(original_run_traceability ${run_traceability})
set(original_run_reals_check ${run_reals_check})

set(run_e2e_tests OFF)
set(run_int_tests OFF)
set(run_perf_tests OFF)
set(run_unittests OFF)
set(run_traceability OFF)
set(run_reals_check OFF)

if ((NOT TARGET c_build_tools) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/c-build-tools/CMakeLists.txt))
    add_subdirectory(deps/c-build-tools)
    set_default_build_options()
endif() 

set(run_e2e_tests ${original_run_e2e_tests})
set(run_int_tests ${original_run_int_tests})
set(run_perf_tests ${original_run_perf_tests})
set(run_unittests ${original_run_unittests})
set(run_traceability ${original_run_traceability})
set(run_reals_check ${original_run_reals_check})

#these are the include folders
#the following "set" statement exports across the project a global variable called MACRO_UTILS_INC_FOLDER that expands to whatever needs to included when using macro_utils
set(MACRO_UTILS_INC_FOLDER ${CMAKE_CURRENT_LIST_DIR}/inc CACHE INTERNAL "this is what needs to be included if using macro utils" FORCE)

include(CTest)
include(GNUInstallDirs)

set(macro_utils_files
    inc/macro_utils/macro_utils.h
    inc/macro_utils/macro_utils_generated.h
)

install(FILES ${macro_utils_files} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/macro_utils")

if("${CMAKE_VERSION}" VERSION_GREATER 3.0.0)
    add_library(macro_utils_c INTERFACE)
    target_include_directories(macro_utils_c
        INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
    install(TARGETS macro_utils_c EXPORT macro_utils_cTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    #Install azure_iot_sdks
    set(package_location "cmake")

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${MACRO_UTILS_C_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    configure_file("configs/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake"
        COPYONLY
    )

    install(EXPORT macro_utils_cTargets
        FILE
            "${PROJECT_NAME}Targets.cmake"
        DESTINATION
            ${package_location}
    )

    install(
        FILES
            "configs/${PROJECT_NAME}Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION
            ${package_location}
    )
else()
    message(STATUS "This version of CMake does not support interface targets. Only the Azure Macro Utils header file will be installed. To use Azure Macro Utils, simply add \"MACRO_UTILS_INC_FOLDER\" to your include directories as specified in the instructions on the GitHub README.")
endif()

if(${run_int_tests})
    add_subdirectory(tests) 
endif()

if(${run_reals_check})
    add_reals_check_target()
endif()
