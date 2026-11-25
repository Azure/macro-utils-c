// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <cstdio>
#include <cstring>

#include "test_helper.h"

#include "macro_utils/macro_utils.h"

#include "mu_define_enum_class_strings_other_tu.h"
#include "mu_define_enum_class_strings_test.h"

/*these types stand in for enums owned by an external C++ SDK*/
namespace external_sdk
{
    enum class sparse_enum
    {
        kFirst = 5,
        kSecond = -1,
        kThird = 100,
        kNotListed = 7
    };

    enum class aliased_enum
    {
        kSum,
        kDefault = kSum,
        kOther
    };
}

using TEST_SPARSE_ENUM_CLASS = external_sdk::sparse_enum;
using TEST_ALIASED_ENUM_CLASS = external_sdk::aliased_enum;

#define TEST_SPARSE_ENUM_CLASS_VALUES \
    kFirst, \
    kSecond, \
    kThird

/*kDefault is listed before kSum although it is declared after it*/
#define TEST_ALIASED_ENUM_CLASS_VALUES \
    kDefault, \
    kSum, \
    kOther

MU_DEFINE_ENUM_CLASS_STRINGS(TEST_SPARSE_ENUM_CLASS, TEST_SPARSE_ENUM_CLASS_VALUES)
MU_DEFINE_ENUM_CLASS_STRINGS(TEST_ALIASED_ENUM_CLASS, TEST_ALIASED_ENUM_CLASS_VALUES)

static int MU_ENUM_TO_STRING_returns_the_name_of_each_listed_enum_class_value(void)
{
    // act
    const char* first = MU_ENUM_TO_STRING(TEST_SPARSE_ENUM_CLASS, TEST_SPARSE_ENUM_CLASS::kFirst);
    const char* second = MU_ENUM_TO_STRING(TEST_SPARSE_ENUM_CLASS, TEST_SPARSE_ENUM_CLASS::kSecond);
    const char* third = MU_ENUM_TO_STRING(TEST_SPARSE_ENUM_CLASS, TEST_SPARSE_ENUM_CLASS::kThird);

    // assert
    POOR_MANS_ASSERT(strcmp("kFirst", first) == 0);
    POOR_MANS_ASSERT(strcmp("kSecond", second) == 0);
    POOR_MANS_ASSERT(strcmp("kThird", third) == 0);

    return 0;
}

static int MU_ENUM_TO_STRING_returns_UNKNOWN_for_an_enum_class_value_not_in_the_list(void)
{
    // act
    const char* not_listed = MU_ENUM_TO_STRING(TEST_SPARSE_ENUM_CLASS, TEST_SPARSE_ENUM_CLASS::kNotListed);

    // assert
    POOR_MANS_ASSERT(strcmp("UNKNOWN", not_listed) == 0);

    return 0;
}

static int MU_ENUM_TO_STRING_returns_the_first_listed_name_for_duplicate_enum_class_values(void)
{
    // act
    const char* aliased = MU_ENUM_TO_STRING(TEST_ALIASED_ENUM_CLASS, TEST_ALIASED_ENUM_CLASS::kSum);

    // assert
    POOR_MANS_ASSERT(strcmp("kDefault", aliased) == 0);

    return 0;
}

static int MU_ENUM_TO_STRING_returns_the_name_from_an_enum_class_stringifier_defined_in_another_translation_unit(void)
{
    // act
    const char* declared = MU_ENUM_TO_STRING(TEST_DECLARED_ENUM_CLASS, TEST_DECLARED_ENUM_CLASS::kDeclaredSecond);

    // assert
    POOR_MANS_ASSERT(strcmp("kDeclaredSecond", declared) == 0);

    return 0;
}

static int PRI_MU_ENUM_formats_an_enum_class_value_as_its_name_and_number(void)
{
    // arrange
    char formatted[32];

    // act
    int written = snprintf(formatted, sizeof(formatted), "%" PRI_MU_ENUM, MU_ENUM_VALUE(TEST_SPARSE_ENUM_CLASS, TEST_SPARSE_ENUM_CLASS::kSecond));

    // assert
    POOR_MANS_ASSERT(written > 0);
    POOR_MANS_ASSERT(strcmp("kSecond (-1)", formatted) == 0);

    return 0;
}

int run_mu_define_enum_class_strings_tests(void)
{
    POOR_MANS_ASSERT(MU_ENUM_TO_STRING_returns_the_name_of_each_listed_enum_class_value() == 0);
    POOR_MANS_ASSERT(MU_ENUM_TO_STRING_returns_UNKNOWN_for_an_enum_class_value_not_in_the_list() == 0);
    POOR_MANS_ASSERT(MU_ENUM_TO_STRING_returns_the_first_listed_name_for_duplicate_enum_class_values() == 0);
    POOR_MANS_ASSERT(MU_ENUM_TO_STRING_returns_the_name_from_an_enum_class_stringifier_defined_in_another_translation_unit() == 0);
    POOR_MANS_ASSERT(PRI_MU_ENUM_formats_an_enum_class_value_as_its_name_and_number() == 0);

    return 0;
}
