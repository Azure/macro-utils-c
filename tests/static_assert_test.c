// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "macro_utils/macro_utils.h"
#include <string.h>
#include "static_assert_test.h"

#include <stdbool.h>
#include <inttypes.h>

int run_static_assert_tests(void)
{
    STATIC_ASSERT(1 + 1 == 2);
    STATIC_ASSERT(sizeof(uint32_t) == sizeof(int32_t));
    STATIC_ASSERT('a' == 'a');

    STATIC_ASSERT(1 + 1 == 2 && 2 + 2 == 4);
    STATIC_ASSERT(1 + 1 == 2 && 'a' == 'a');
    STATIC_ASSERT(1 + 1 == 2 && sizeof(uint32_t) == 4Ui64);
    STATIC_ASSERT('a' == 'a' && sizeof(uint32_t) == 4Ui64);

    STATIC_ASSERT(1 + 1 == 2 && 2 + 2 == 4 && 3 + 3 == 6);
    STATIC_ASSERT(1 + 1 == 2 && 'a' == 'a' && sizeof(uint32_t) == 4Ui64);

    /*Test STATIC_ASSERT fail, compile shall fail in these test cases*/
    // STATIC_ASSERT(1 + 1 == 3);
    // STATIC_ASSERT(sizeof(uint32_t) != sizeof(int32_t));
    // STATIC_ASSERT('a' == 'b');
    // STATIC_ASSERT(1 + 1 == 3 && 2 + 2 == 4);
    // STATIC_ASSERT(1 + 1 == 2 && 'a' == 'b');
    // STATIC_ASSERT(1 + 1 == 3 && sizeof(uint32_t) == 4Ui64);
    // STATIC_ASSERT('a' == 'b' && sizeof(uint32_t) == 4Ui64);
    // STATIC_ASSERT(1 + 1 == 2 && 2 + 2 == 5 && 3 + 3 == 6);
    // STATIC_ASSERT(1 + 1 == 2 && 'a' == 'c' && sizeof(uint32_t) == 4Ui64);
    return 0;
}
