#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

include("${CMAKE_CURRENT_LIST_DIR}/azure_macro_utils_cTargets.cmake")

get_target_property(AZURE_MACRO_UTILS_C_INCLUDES azure_macro_utils_c INTERFACE_INCLUDE_DIRECTORIES)

set(AZURE_MACRO_UTILS_C_INCLUDES ${AZURE_MACRO_UTILS_C_INCLUDES} CACHE INTERNAL "")
