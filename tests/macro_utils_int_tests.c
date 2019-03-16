// Copyright(C) Microsoft Corporation.All rights reserved.

#include <string.h>
#include <stdio.h>

#include "azure_macro_utils/macro_utils.h"

/*Ctest fails when main returns anything != 0*/

/*defining a simple enum with the constituend test1_a=2, test1_b=3, note: this tests that a DEFINE_ENUM_STRING_2 is not mandatory*/
MU_DEFINE_ENUM_2(test1, test1_a, 2, test1_b, 3);


/*this checks that an enum with 1 value can still be constructed*/
MU_DEFINE_ENUM_2(test2, test2_a, 45);

/*this is bringing in the enum called TEST3_ENUM and main will call the "stringify" of this enum*/
#include "define_enum_2_test.h"
int main(void)
{
    int result = 0;

    test1 someUnusedVariable;
    (void)someUnusedVariable;

    const char* TEST2_value_0 = MU_ENUM_TO_STRING_2(TEST3_ENUM, 0);
    if (TEST2_value_0 == NULL)
    {
        (void)printf("TEST2_ENUM should not return NULL\n");
        result++;
    }
    else
    {
        if (strcmp("NULL", TEST2_value_0) != 0)
        {
            (void)printf("MU_ENUM_TO_STRING_2(TEST2_ENUM, 0) should return \"NULL\"\n");
            result++;
        }
    }
    
    const char* TEST3_value_2 = MU_ENUM_TO_STRING_2(TEST3_ENUM, 2);
    if (TEST3_value_2 == NULL)
    {
        (void)printf("TEST3_ENUM should know how to compute the string for <<2>>, but it did not\n");
        result++;
    }
    else
    {
        if (strcmp("test3_a", TEST3_value_2)!=0)
        {
            (void)printf("MU_ENUM_TO_STRING_2(TEST3_ENUM, 2) computed some wrong value %s while %s was expected", TEST3_value_2, "test3_a" "\n");
            result++;
        }
    }

    if (result == 0)
    {
        (void)printf("All tests passed\n");
    }
    else
    {
        (void)printf("%d tests failed\n", result);
    }

    return result;
}