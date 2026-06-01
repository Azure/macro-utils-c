// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <wchar.h>
#include <string.h>

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_tostring_test.h"

int run_mu_tostring_tests(void)
{
    POOR_MANS_ASSERT(strcmp("hagauaga", MU_TOSTRING(hagauaga)) == 0);

    POOR_MANS_ASSERT(strcmp("", MU_TOSTRING()) == 0);

    POOR_MANS_ASSERT(wcscmp(L"hagauaga", MU_TOWSTRING(hagauaga)) == 0);

    POOR_MANS_ASSERT(wcscmp(L"", MU_TOWSTRING()) == 0);

    return 0;
}
