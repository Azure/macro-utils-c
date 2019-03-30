// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>

#include "azure_macro_utils/macro_utils.h"

#include "mu_eat_empty_args.h"

/*this is both a "does it compile"? and a "does it produce the right values?" test*/
/*this file wants to test just the MOO_EAT_EMPTY_ARGS feature*/

#define EMPTY_MACRO 

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS()

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(EMPTY_MACRO)

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(,)

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(EMPTY_MACRO, )

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(, EMPTY_MACRO)

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(EMPTY_MACRO, EMPTY_MACRO )

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(EMPTY_MACRO, EMPTY_MACRO, EMPTY_MACRO)


/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(EMPTY_MACRO, EMPTY_MACRO, )

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(EMPTY_MACRO, , EMPTY_MACRO)

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(, EMPTY_MACRO, EMPTY_MACRO)

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(, , EMPTY_MACRO)

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(, EMPTY_MACRO, )

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(EMPTY_MACRO, , )

/*the below line is expected to stop the compiler if it expands to anything... sort of*/
MU_EAT_EMPTY_ARGS(, , )


#define POOR_MANS_ASSERT_AND_RETURN(condition)                                                          \
do                                                                                                      \
{                                                                                                       \
    if (!(condition))                                                                                   \
    {                                                                                                   \
        printf("condition \"" #condition "\" in LINE=" MU_TOSTRING(__LINE__) " was UNEXPECTEDLY FALSE\n");          \
        return MU_FAILURE;                                                                              \
    }                                                                                                   \
} while (0)


int run_mu_eat_empty_args_test(void)
{
    int tester = 0;

    tester = MU_EAT_EMPTY_ARGS() + tester; /*so this doesn't expand to anything, but should still compile, result = + result is  perfectly valid C code*/ /*it could also expand to "0" :(*/
    POOR_MANS_ASSERT_AND_RETURN(tester == 0);

    tester = MU_EAT_EMPTY_ARGS(1); /*there's nothing to eat from "1", so it expands to "1"*/
    POOR_MANS_ASSERT_AND_RETURN(tester == 1);
    

    /*see that it eats / doesn't eat from 2 arguments*/

    { /*scope because of repetitive naure of tests and copy&paste*/
        int testerArray_1[] = { MU_EAT_EMPTY_ARGS(42 + 1,) }; /*eats 1 empty argument, expands to "42+1"*/
        POOR_MANS_ASSERT_AND_RETURN(1 == (sizeof(testerArray_1) / sizeof(testerArray_1[0])));
        POOR_MANS_ASSERT_AND_RETURN(42 + 1 == testerArray_1[0]);
    }

    { /*scope because of repetitive naure of tests and copy&paste*/
        int testerArray_2[] = { MU_EAT_EMPTY_ARGS(42 + 2,) }; /*eats 1 empty argument, expands to "42+1"*/
        POOR_MANS_ASSERT_AND_RETURN(1 == (sizeof(testerArray_2) / sizeof(testerArray_2[0])));
        POOR_MANS_ASSERT_AND_RETURN(42 + 2 == testerArray_2[0]);
    }
    
    {
        int testerArray_3[] = { MU_EAT_EMPTY_ARGS(42 + 3 ,42 + 4) }; /*doesn't eat anything*/

        POOR_MANS_ASSERT_AND_RETURN(2 == (sizeof(testerArray_3) / sizeof(testerArray_3[0])));
        
        POOR_MANS_ASSERT_AND_RETURN(testerArray_3[0] == 42 + 3);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_3[1] == 42 + 4);
    }

    /*see that it eats / doesn't eat from 3 arguments*/
    {
        int testerArray_4[] = { MU_EAT_EMPTY_ARGS(42 + 5 ,42 + 6, 42 + 7) }; /*doesn't eat anything*/

        POOR_MANS_ASSERT_AND_RETURN(3 == (sizeof(testerArray_4) / sizeof(testerArray_4[0])));
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[0] == 42 + 5);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[1] == 42 + 6);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[2] == 42 + 7);
    }

    /*see that it eats / doesn't eat from 3 arguments*/
    {
        int testerArray_4[] = { MU_EAT_EMPTY_ARGS( ,42 + 6, 42 + 7) }; /*eats first*/

        POOR_MANS_ASSERT_AND_RETURN(2 == (sizeof(testerArray_4) / sizeof(testerArray_4[0])));
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[0] == 42 + 6);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[1] == 42 + 7);
    }

    /*see that it eats / doesn't eat from 3 arguments*/
    {
        int testerArray_4[] = { MU_EAT_EMPTY_ARGS(42 + 5 ,, 42 + 7) }; /*eat middle*/

        POOR_MANS_ASSERT_AND_RETURN(2 == (sizeof(testerArray_4) / sizeof(testerArray_4[0])));
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[0] == 42 + 5);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[1] == 42 + 7);
    }

    /*see that it eats / doesn't eat from 3 arguments*/
    {
        int testerArray_4[] = { MU_EAT_EMPTY_ARGS(42 + 5 ,42 + 6, ) }; /*eats last*/

        POOR_MANS_ASSERT_AND_RETURN(2 == (sizeof(testerArray_4) / sizeof(testerArray_4[0])));
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[0] == 42 + 5);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[1] == 42 + 6);
    }

    /*see that it eats / doesn't eat from 3 arguments*/
    {
        int testerArray_4[] = { MU_EAT_EMPTY_ARGS(42 + 5 , , ) }; /*eats middle and last*/

        POOR_MANS_ASSERT_AND_RETURN(1 == (sizeof(testerArray_4) / sizeof(testerArray_4[0])));
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[0] == 42 + 5);
    }

    /*see that it eats / doesn't eat from 3 arguments*/
    {
        int testerArray_4[] = { MU_EAT_EMPTY_ARGS(,42 + 6, ) }; /*eats first and last*/

        POOR_MANS_ASSERT_AND_RETURN(1 == (sizeof(testerArray_4) / sizeof(testerArray_4[0])));
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[0] == 42 + 6);
    }

    /*see that it eats / doesn't eat from 3 arguments*/
    {
        int testerArray_4[] = { MU_EAT_EMPTY_ARGS(, , 42 + 7) }; /*eats first and middle*/

        POOR_MANS_ASSERT_AND_RETURN(1 == (sizeof(testerArray_4) / sizeof(testerArray_4[0])));
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[0] == 42 + 7);
    }


    /*see that it eats / doesn't eat from 10 arguments*/
    {
        int testerArray_4[] = { MU_EAT_EMPTY_ARGS (1,2,3,4,5,6,7,8,9,10)}; /*eats nothing*/

        POOR_MANS_ASSERT_AND_RETURN(10 == (sizeof(testerArray_4) / sizeof(testerArray_4[0])));
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[0] == 1);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[1] == 2);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[2] == 3);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[3] == 4);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[4] == 5);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[5] == 6);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[6] == 7);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[7] == 8);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[8] == 9);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[9] == 10);
    }

    /*see that it eats / doesn't eat from 10 arguments*/
    {
        int testerArray_4[] = { MU_EAT_EMPTY_ARGS(1,2, ,4,5,6,7,8,9,10) }; /*eats 3*/

        POOR_MANS_ASSERT_AND_RETURN(9 == (sizeof(testerArray_4) / sizeof(testerArray_4[0])));
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[0] == 1);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[1] == 2);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[2] == 4);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[3] == 5);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[4] == 6);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[5] == 7);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[6] == 8);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[7] == 9);
        POOR_MANS_ASSERT_AND_RETURN(testerArray_4[8] == 10);
    }

    return 0;
}
