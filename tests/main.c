// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>

#include "define_enum_2_test.h"
#include "mu_eat_empty_args_test.h"

int main(void)
{
    int result;
    result = run_define_enum_2_test();
    if (result != 0)
    {
        printf("failures in run_define_enum_2_test\n");
        return result;
    }

    result = run_mu_eat_empty_args_test();
    if (result != 0)
    {
        printf("failures in run_mu_eat_empty_args_test\n");
        return result;
    }

    return 0;
}

