#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

cmake_minimum_required(VERSION 2.8.11)
    
project(azure_macro_utils_c)

if(DEFINED MACRO_UTILS_INC_FOLDER)
    return()
endif()

#these are the include folders
#the following "set" statement exports across the project a global variable called MACRO_UTILS_INC_FOLDER that expands to whatever needs to included when using macro_utils
set(MACRO_UTILS_INC_FOLDER ${CMAKE_CURRENT_LIST_DIR}/inc CACHE INTERNAL "this is what needs to be included if using macro utils" FORCE)

include_folders(${MACRO_UTILS_INC_FOLDER})



#if(${use_installed_dependencies})
#    #Set CMAKE_INSTALL_LIBDIR if not defined
#    include(GNUInstallDirs)
#
#    #Install azure_iot_sdks
#    set(package_location "cmake")
#
#    include(CMakePackageConfigHelpers)
#
#    write_basic_package_version_file(
#        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
#        VERSION ${IOT_SDK_VERSION}
#        COMPATIBILITY SameMajorVersion
#    )
#
#    configure_file("configs/${PROJECT_NAME}Config.cmake"
#        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake"
#        COPYONLY
#    )
#
#    install(EXPORT azure_iot_sdksTargets
#        FILE
#            "${PROJECT_NAME}Targets.cmake"
#        DESTINATION
#            ${package_location}
#    )
#
#    install(
#        FILES
#            "configs/${PROJECT_NAME}Config.cmake"
#            "configs/${PROJECT_NAME}Functions.cmake"
#            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
#        DESTINATION
#            ${package_location}
#    )
#
#else()
#    message(WARNING "This package may only be installed when 'use_installed_dependencies' is ON")
#endif()