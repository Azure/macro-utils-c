// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "test_helper.h"

#include "azure_macro_utils/macro_utils.h"

#include "mu_for_each_1_test.h"

/*identity macro with comma*/
#define IDCOMMA(X) X ,

static int a[] = { MU_FOR_EACH_1(IDCOMMA, 1, 2) }; /*expands to {1, 2, }, an array with 2(two) elements.*/

/*identity macro without comma*/
#define ONCE(X) X
static const char* someString = MU_FOR_EACH_1(ONCE, "s", "o", "m", "e"); /*expands to "s" "o" "m" "e". All strings are concatenated by PP, so this results in "some" string finally*/

/*expands to two tokens*/
#define TWICE(X) X X

/*expands to three tokens*/
#define THRICE(X) X X X

/*a more interesting test*/
static const char* sixem = MU_FOR_EACH_1(THRICE, MU_FOR_EACH_1(TWICE, "A", "B"));
/*                                               ^-expands to TWICE("A") TWICE("B") => "A" "A" "B" "B" => "AABB" */
/*                         ^- expands to THRICE("AABB")=> "AABB" "AABB" "AABB" => "AABBAABBAABB"                 */

int run_mu_for_each_1_tests(void)
{
    POOR_MANS_ASSERT((sizeof(a) / sizeof(a[0])) == 2);
    POOR_MANS_ASSERT(a[0] == 1);
    POOR_MANS_ASSERT(a[1] == 2);

    POOR_MANS_ASSERT(someString[0] == 's');
    POOR_MANS_ASSERT(someString[1] == 'o');
    POOR_MANS_ASSERT(someString[2] == 'm');
    POOR_MANS_ASSERT(someString[3] == 'e');
    POOR_MANS_ASSERT(someString[4] == '\0');

    POOR_MANS_ASSERT(sixem[0] == 'A');
    POOR_MANS_ASSERT(sixem[1] == 'A');
    POOR_MANS_ASSERT(sixem[2] == 'B');
    POOR_MANS_ASSERT(sixem[3] == 'B');
    POOR_MANS_ASSERT(sixem[4] == 'A');
    POOR_MANS_ASSERT(sixem[5] == 'A');
    POOR_MANS_ASSERT(sixem[6] == 'B');
    POOR_MANS_ASSERT(sixem[7] == 'B');
    POOR_MANS_ASSERT(sixem[8] == 'A');
    POOR_MANS_ASSERT(sixem[9] == 'A');
    POOR_MANS_ASSERT(sixem[10] == 'B');
    POOR_MANS_ASSERT(sixem[11] == 'B');
    POOR_MANS_ASSERT(sixem[12] == '\0');
    
    /*can MU_FOR_EACH_1 take an empty argument?*/
    POOR_MANS_ASSERT(MU_ISEMPTY(MU_FOR_EACH_1(ONCE, )) == 1);

    return 0;
}
