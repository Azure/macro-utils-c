// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_array_test.h"

static const char* names_1[] = { "Ionescu" };
static const char* names_2[] = { "Popescu", "Ionescu" };
static const char* names_3[] = { "Georgescu", "Popescu", "Ionescu" };

static const wchar_t* wnames_1[] = { L"Ionescu" };
static const wchar_t* wnames_2[] = { L"Popescu", L"Ionescu" };
static const wchar_t* wnames_3[] = { L"Georgescu", L"Popescu", L"Ionescu" };

static int run_mu_array_wstring_tests(void)
{
    char temp[1000]; /*sufficient to hold all the names representations*/
    int result;

    /*tests for PRI_ARRAY/ARRAY_VALUES*/

    /*array of size 0*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(wchar_ptr_t, wnames_1, 0)); /*array size is harcoded 0*/
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{  }") == 0);

    /*array of size 1*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(wchar_ptr_t, wnames_1, sizeof(wnames_1) / sizeof(wnames_1[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Ionescu }") == 0);

    /*array of size 2*/
    /*printing all the array*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(wchar_ptr_t, wnames_2, sizeof(wnames_2) / sizeof(wnames_2[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu, [1]=Ionescu }") == 0);

    /*printing just the first name*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(wchar_ptr_t, wnames_2, 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu }") == 0);

    /*array of size 3*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(wchar_ptr_t, wnames_3, sizeof(wnames_3) / sizeof(wnames_3[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Georgescu, [1]=Popescu, [2]=Ionescu }") == 0);

    return 0;
}


static int run_mu_array_string_tests(void)
{
    int result;

    result = run_mu_array_wstring_tests();
    POOR_MANS_ASSERT(result == 0);

    char temp[1000]; /*sufficient to hold all the names representations*/

    /*array of size 0*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(char_ptr_t, names_1, 0)); /*array size is harcoded 0*/
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{  }") == 0);

    /*array of size 0*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(char_ptr_t, names_1, sizeof(names_1) / sizeof(names_1[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Ionescu }") == 0);

    /*array of size 2*/
    /*printing all the array*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(char_ptr_t, names_2, sizeof(names_2) / sizeof(names_2[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu, [1]=Ionescu }") == 0);

    /*printing just the first name*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(char_ptr_t, names_2, 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Popescu }") == 0);

    /*array of size 3*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(char_ptr_t, names_3, sizeof(names_3) / sizeof(names_3[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=Georgescu, [1]=Popescu, [2]=Ionescu }") == 0);

    return 0;
}

/*arrays of structs can be printed*/

typedef struct POINT_TAG
{
    int x;
    int y;
} POINT;

static POINT points[] = { {1,2}, {30,40}, {50,60} };

#define PRI_POINT "s(POINT){ .x=%d, .y=%d }"
#define POINT_VALUE(p) "", (p).x, (p).y

MU_PRINT_ARRAY_FUNCTION_DECLARE(POINT);
MU_PRINT_ARRAY_FUNCTION_DEFINE(POINT, PRI_POINT, POINT_VALUE);


static int run_mu_array_POINT_tests(void)
{
    char temp[1000]; /*sufficient to hold all the points representations*/
    int result;
    /*array of size 0*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(POINT, points, 0)); /*array size is harcoded 0*/
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{  }") == 0);

    /*array of size 1*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(POINT, points, 1));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=(POINT){ .x=1, .y=2 } }") == 0);

    /*array of size 2*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(POINT, points, 2));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=(POINT){ .x=1, .y=2 }, [1]=(POINT){ .x=30, .y=40 } }") == 0);

    /*array of size 3*/
    result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY "", ARRAY_VALUES(POINT, points, 3));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(temp, "{ [0]=(POINT){ .x=1, .y=2 }, [1]=(POINT){ .x=30, .y=40 }, [2]=(POINT){ .x=50, .y=60 } }") == 0);

    return 0;
}

/*arrays of arrays of strings can also be printed???*/
typedef struct ARRAY_OF_STRINGS_TAG
{
    int n;
    const char** strings;
}ARRAY_OF_STRINGS;

#define PRI_ARRAY_OF_STRINGS "s{ .n=%d, .strings=%" PRI_ARRAY " }"
#define ARRAY_OF_STRINGS_VALUE(aos) "", (aos).n, ARRAY_VALUES(char_ptr_t, (aos).strings, (aos).n)

MU_PRINT_ARRAY_FUNCTION_DECLARE(ARRAY_OF_STRINGS);
MU_PRINT_ARRAY_FUNCTION_DEFINE(ARRAY_OF_STRINGS, PRI_ARRAY_OF_STRINGS, ARRAY_OF_STRINGS_VALUE);

typedef struct ARRAY_OF_ARRAY_OF_STRINGS_TAG
{
    int n;
    /*cannot be ARRAY_OF_STRINGS arrays[]; because error C2233: 'arrays': arrays of objects containing zero-size arrays are illegal*/
    ARRAY_OF_STRINGS* arrays;
}ARRAY_OF_ARRAY_OF_STRINGS;

#define PRI_ARRAY_OF_ARRAY_OF_STRINGS "s{ .n=%d, .arrays=%" PRI_ARRAY " }"
#define ARRAY_OF_ARRAY_OF_STRINGS_VALUE(aoas) "", (aoas).n, ARRAY_VALUES(ARRAY_OF_STRINGS, (aoas).arrays, (aoas).n)

MU_PRINT_ARRAY_FUNCTION_DECLARE(ARRAY_OF_ARRAY_OF_STRINGS);
MU_PRINT_ARRAY_FUNCTION_DEFINE(ARRAY_OF_ARRAY_OF_STRINGS, PRI_ARRAY_OF_ARRAY_OF_STRINGS, ARRAY_OF_ARRAY_OF_STRINGS_VALUE);

static int run_mu_array_ARRAY_OF_ARRAY_OF_STRINGS_tests(void)
{
    const char* one[] = {"Single"};
    const char* two[] = {"Husband", "Wife"};
    const char* three[] = {"Father", "Mother", "Child"};

    ARRAY_OF_STRINGS arrays[] = {
        { sizeof(one)/sizeof(one[0]), one},
        { sizeof(two) / sizeof(two[0]), two },
        { sizeof(three) / sizeof(three[0]), three }
    };

    ARRAY_OF_ARRAY_OF_STRINGS array_of_arrays = {
        sizeof(arrays)/sizeof(arrays[0]),
        arrays
    };

    char temp[2000]; /*sufficient*/
    int result = snprintf(temp, sizeof(temp), "%" PRI_ARRAY_OF_ARRAY_OF_STRINGS "", ARRAY_OF_ARRAY_OF_STRINGS_VALUE(array_of_arrays));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));
    POOR_MANS_ASSERT(strcmp(
        "{ .n=3, .arrays={ [0]={ .n=1, .strings={ [0]=Single } }, [1]={ .n=2, .strings={ [0]=Husband, [1]=Wife } }, [2]={ .n=3, .strings={ [0]=Father, [1]=Mother, [2]=Child } } } }",
        temp) == 0);
    return 0;
}

#define PRI_JUST_CHAR "c"
#define JUST_CHAR_VALUE(c) (c)

MU_PRINT_ARRAY_FUNCTION_DECLARE(char);
MU_PRINT_ARRAY_FUNCTION_DEFINE(char, PRI_JUST_CHAR, JUST_CHAR_VALUE);

static int run_mu_array_around_max_buffer_tests(void)
{
    char temp[MU_ARRAY_PRINT_CAPACITY]; /*printing this array FOR SURE it would exceed the printing buffer*/
    (void)memset(temp, '3', sizeof(temp));

    char buffer[MU_ARRAY_PRINT_CAPACITY * 20]; /*ample space to store any possible result*/

    int result = snprintf(buffer, sizeof(buffer), "%" PRI_ARRAY "", ARRAY_VALUES(char, temp, sizeof(temp) / sizeof(temp[0])));
    POOR_MANS_ASSERT(result >= 0 && result < sizeof(temp));

    size_t size = strlen(buffer);
    POOR_MANS_ASSERT(size < MU_ARRAY_PRINT_CAPACITY);

    /*because we are forcing a buffer overflow here, we expect that the output will end in MU_NOT_ENOUGH_BUFFER_STR }*/
    POOR_MANS_ASSERT(strcmp(buffer + size - (sizeof(MU_NOT_ENOUGH_BUFFER_STR MU_CLOSING_BRACE_STR) - 1), MU_NOT_ENOUGH_BUFFER_STR MU_CLOSING_BRACE_STR) == 0);

    /*at this point, buffer contains { [0]=3, [1]=3, ... , [462]=3, [463]=3 NOT_ENOUGH_BUFFER } when MU_ARRAY_PRINT_CAPACITY is 4096*/

    return 0;
}

int run_mu_array_tests(void)
{
    int result;
    result = run_mu_array_string_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_array_wstring_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_array_POINT_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_array_ARRAY_OF_ARRAY_OF_STRINGS_tests();
    POOR_MANS_ASSERT(result == 0);

    result = run_mu_array_around_max_buffer_tests();

    return 0;
}
