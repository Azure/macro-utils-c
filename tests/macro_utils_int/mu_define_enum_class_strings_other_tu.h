// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MU_DEFINE_ENUM_CLASS_STRINGS_OTHER_TU_H
#define MU_DEFINE_ENUM_CLASS_STRINGS_OTHER_TU_H

#ifdef __cplusplus

#include "macro_utils/macro_utils.h"

namespace external_sdk_other_tu
{
    enum class declared_enum
    {
        kDeclaredFirst,
        kDeclaredSecond
    };
}

using TEST_DECLARED_ENUM_CLASS = external_sdk_other_tu::declared_enum;

#define TEST_DECLARED_ENUM_CLASS_VALUES \
    kDeclaredFirst, \
    kDeclaredSecond

MU_DECLARE_ENUM_STRINGS(TEST_DECLARED_ENUM_CLASS, TEST_DECLARED_ENUM_CLASS_VALUES)

#endif /*__cplusplus*/

#endif // MU_DEFINE_ENUM_CLASS_STRINGS_OTHER_TU_H
