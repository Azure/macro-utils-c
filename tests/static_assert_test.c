// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "macro_utils/macro_utils.h"
#include "static_assert_test.h"

int run_static_assert_tests(void)
{
    MU_STATIC_ASSERT(1 + 1 == 2);
    MU_STATIC_ASSERT(sizeof(uint32_t) == sizeof(int32_t));
    MU_STATIC_ASSERT('a' == 'a');

    MU_STATIC_ASSERT(1 + 1 == 2 && 2 + 2 == 4);
    MU_STATIC_ASSERT(1 + 1 == 2 && 'a' == 'a');
    MU_STATIC_ASSERT(1 + 1 == 2 && sizeof(uint32_t) == sizeof(int32_t));
    MU_STATIC_ASSERT('a' == 'a' && sizeof(uint32_t) == sizeof(int32_t));

    MU_STATIC_ASSERT(1 + 1 == 2 && 2 + 2 == 4 && 3 + 3 == 6);
    MU_STATIC_ASSERT(1 + 1 == 2 && 'a' == 'a' && sizeof(uint32_t) == sizeof(int32_t));

    /*Test STATIC_ASSERT fail, compile shall fail in these test cases*/
    // MU_STATIC_ASSERT(1 + 1 == 3);
    // MU_STATIC_ASSERT(sizeof(uint32_t) != sizeof(int32_t));
    // MU_STATIC_ASSERT('a' == 'b');
    // MU_STATIC_ASSERT(1 + 1 == 3 && 2 + 2 == 4);
    // MU_STATIC_ASSERT(1 + 1 == 2 && 'a' == 'b');
    // MU_STATIC_ASSERT(1 + 1 == 3 && sizeof(uint32_t) == sizeof(int32_t));
    // MU_STATIC_ASSERT('a' == 'b' && sizeof(uint32_t) == sizeof(int32_t));
    // MU_STATIC_ASSERT(1 + 1 == 2 && 2 + 2 == 5 && 3 + 3 == 6);
    // MU_STATIC_ASSERT(1 + 1 == 2 && 'a' == 'c' && sizeof(uint32_t) == sizeof(int32_t));
    return 0;
}
