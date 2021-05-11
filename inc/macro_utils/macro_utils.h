// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MACRO_UTILS_H
#define MACRO_UTILS_H

#include "macro_utils/macro_utils_generated.h"

#ifdef __cplusplus
#include <cstring>
#include <cstddef>
#include <ctime>
extern "C" {
#else
#include <string.h>
#include <stddef.h>
#include <time.h>
#endif

#if (defined OPTIMIZE_RETURN_CODES)
    #define MU_FAILURE 1
#else
    #define MU_FAILURE __LINE__
#endif

/*"pointer or NULL" macro - because when printf-ing arguments NULL is not valid for %s (section 7.1.4 of C11 standard) */
#define MU_P_OR_NULL(p) (((p)!=NULL)?(p):"NULL")
#define MU_WP_OR_NULL(p) (((p)!=NULL)?(p):L"NULL")

#define MU_TOSTRING_(x) #x
#define MU_TOSTRING(x) MU_TOSTRING_(x)

#define MU_TRIGGER_PARENTHESIS(...) ,

#if defined(_MSC_VER) && (_MSC_VER<1920)
#define MU_LPAREN (
#endif

#define MU_C2_(x,y) x##y
#define MU_C2(x,y) MU_C2_(x,y)

/*the following macros (MU_C2A. MU_C2B, MU_C2C) exist only to have a different name than MU_C2 but provide the same functionality*/
/*this is needed to avoid recursion of macro expansions in certain cases*/
#define MU_PASTEA_(x,y) x##y
#define MU_C2A(x,y) MU_PASTEA_(x,y)

#define MU_PASTEB_(x,y) x##y
#define MU_C2B(x,y) MU_PASTEB_(x,y)

#define MU_PASTEC_(x,y) x##y
#define MU_C2C(x,y) MU_PASTEC_(x,y)

#define MU_C3(x,y,z) MU_C2(x, MU_C2(y,z))

#define MU_C4(x,y,z, u) MU_C2(MU_C2(x,y), MU_C2(z,u))

#define MU_C5(x,y,z,u, v) MU_C2(MU_C4(x,y, z, u), v)

#define MU_C1_(x) x

#define MU_C1(x) MU_C1_(x)

#define MU_C2STRING(x,y) x y

#define MU_C3STRING(x,y,z) x y z

#define MU_C4STRING(x,y,z,u) x y z u

#define MU_C5STRING(x,y,z,u,v) x y z u v

/* we need some sort of macro that does:
MU_IF(0, "true", "false") => "false"
MU_IF(1, "true", "false") => "true"
MU_IF(X, "true", "false") => "true"
*/

#define MU_INTERNALIF(x) MU_INTERNALIF##x
#define MU_INTERNALIF0

#define MU_ISZERO(x) MU_COUNT_ARG(MU_INTERNALIF(x))

#define MU_IF(condition, trueBranch, falseBranch) MU_C2(MU_IF,MU_ISZERO(condition))(trueBranch, falseBranch)
#define MU_IF0(trueBranch, falseBranch) falseBranch
#define MU_IF1(trueBranch, falseBranch) trueBranch

/*the following macro want to eat empty arguments from a list */
/*examples:                                                   */
/*MU_EAT_EMPTY_ARGS(, , X) expands to X                       */

#define MU_EXPAND_TO_NOTHING(arg)
#define MU_EAT_EMPTY_ARG(arg_count, arg) MU_IF(MU_ISEMPTY(arg),,arg) MU_IF(MU_ISEMPTY(arg),MU_EXPAND_TO_NOTHING,MU_IFCOMMALOGIC)(MU_DEC(arg_count))
#define MU_EAT_EMPTY_ARGS(...) MU_FOR_EACH_1_COUNTED(MU_EAT_EMPTY_ARG, __VA_ARGS__)

#define MU_DEFINE_ENUMERATION_CONSTANT(x) x,
#define MU_DEFINE_METADATA_ENUMERATION_VALUE(x) MU_C2(enum_value_typedef_, x),

/*MU_DEFINE_ENUM_WITHOUT_INVALID goes to header*/
#define MU_DEFINE_ENUM_WITHOUT_INVALID(enumName, ...) typedef enum MU_C2(enumName, _TAG) { MU_FOR_EACH_1(MU_DEFINE_ENUMERATION_CONSTANT, __VA_ARGS__)} enumName; \
    typedef enum MU_C3(enum_value_metadata_, enumName, _TAG) { MU_FOR_EACH_1(MU_DEFINE_METADATA_ENUMERATION_VALUE, __VA_ARGS__) MU_C3(enum_value_metadata_, enumName, _VALUE_COUNT) = MU_COUNT_ARG(__VA_ARGS__)} MU_C2(enum_value_metadata_, enumName); \
    extern const char* MU_C2(enumName,Strings)(enumName value); \
    extern int MU_C2(enumName, _FromString)(const char* enumAsString, enumName* destination);

// this macro is a wrapper on top of MU_DEFINE_ENUM_WITHOUT_INVALID, adding an _INVALID value as the first enum value in the enum
#define MU_DEFINE_ENUM(enumName, ...) \
    MU_DEFINE_ENUM_WITHOUT_INVALID(enumName, MU_C2(enumName, _INVALID), __VA_ARGS__)

#define MU_DEFINE_ENUMERATION_CONSTANT_AS_WIDESTRING(x) MU_C2(L, MU_TOSTRING(x)) , 
#define MU_DEFINE_ENUMERATION_CONSTANT_AS_STRING(x) MU_TOSTRING(x) , 
/*MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID goes to .c*/
#define MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID(enumName, ...) const char* MU_C2(enumName, StringStorage)[MU_COUNT_ARG(__VA_ARGS__)] = {MU_FOR_EACH_1(MU_DEFINE_ENUMERATION_CONSTANT_AS_STRING, __VA_ARGS__)}; \
const char* MU_C2(enumName,Strings)(enumName value)                \
{                                                                  \
    if((int)value<0 || (int)value>=MU_COUNT_ARG(__VA_ARGS__))      \
    {                                                              \
        /*this is an error case*/                                  \
        return "UNKNOWN";                                          \
    }                                                              \
    else                                                           \
    {                                                              \
        return MU_C2(enumName, StringStorage)[value];              \
    }                                                              \
}                                                                  \
int MU_C2(enumName, _FromString)(const char* enumAsString, enumName* destination)  \
{                                                                               \
    if(                                                                         \
        (enumAsString==NULL) || (destination==NULL)                             \
    )                                                                           \
    {                                                                           \
        return MU_FAILURE;                                                      \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        size_t i;                                                               \
        for(i=0;i<MU_COUNT_ARG(__VA_ARGS__);i++)                                \
        {                                                                       \
            if(strcmp(enumAsString, MU_C2(enumName, StringStorage)[i])==0)      \
            {                                                                   \
                *destination = (enumName)i;                                     \
                return 0;                                                       \
            }                                                                   \
        }                                                                       \
        return MU_FAILURE;                                                      \
    }                                                                           \
}                                                                               \

// this macro is a wrapper on top of MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID, adding an _INVALID value as the first enum value in the enum
#define MU_DEFINE_ENUM_STRINGS(enumName, ...) \
    MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID(enumName, MU_C2(enumName, _INVALID), __VA_ARGS__)

#define MU_DEFINE_LOCAL_ENUM_WITHOUT_INVALID(enumName, ...) typedef enum MU_C2(enumName, _TAG) { MU_FOR_EACH_1(MU_DEFINE_ENUMERATION_CONSTANT, __VA_ARGS__)} enumName; \
static const char* MU_C2(enumName, StringStorage)[MU_COUNT_ARG(__VA_ARGS__)] = {MU_FOR_EACH_1(MU_DEFINE_ENUMERATION_CONSTANT_AS_STRING, __VA_ARGS__)}; \
static const char* MU_C2(enumName,Strings)(enumName value)         \
{                                                                  \
    if((int)value<0 || (int)value>=MU_COUNT_ARG(__VA_ARGS__))      \
    {                                                              \
        /*this is an error case*/                                  \
        return "UNKNOWN";                                          \
    }                                                              \
    else                                                           \
    {                                                              \
        return MU_C2(enumName, StringStorage)[value];              \
    }                                                              \
}

// this macro is a wrapper on top of MU_DEFINE_LOCAL_ENUM_WITHOUT_INVALID, adding an _INVALID value as the first enum value in the enum
#define MU_DEFINE_LOCAL_ENUM(enumName, ...) \
    MU_DEFINE_LOCAL_ENUM_WITHOUT_INVALID(enumName, MU_C2(enumName, _INVALID), __VA_ARGS__)

// this macro returns the number of enum values (taking into account that an invalid value is generated)
#define MU_ENUM_VALUE_COUNT(...) (MU_COUNT_ARG(__VA_ARGS__) + 1)
#define MU_ENUM_VALUE_COUNT_WITHOUT_INVALID(...) (MU_COUNT_ARG(__VA_ARGS__))

// this macro returns the number of enum 2 values (taking into account that an invalid value is generated)
#define MU_ENUM_2_VALUE_COUNT(...) ((MU_COUNT_ARG(__VA_ARGS__) / 2) + 1)

#define MU_ENUM_TO_STRING(enumName, enumValue) MU_C2(enumName, Strings)(enumValue)
#define MU_STRING_TO_ENUM(stringValue, enumName, addressOfEnumVariable) MU_C2(enumName, _FromString)(stringValue, addressOfEnumVariable)

#define MU_EMPTY()
#define MACRO_UTILS_DELAY(id) id MU_EMPTY MU_LPAREN )

#define MU_DEFINE_ENUMERATION_CONSTANT_2(enumerationConstant, constantExpression) enumerationConstant = constantExpression,

#define MU_DECLARE_ENUM_STRINGS_2(enumIdentifier, ...) extern const char* MU_C3(MU_, enumIdentifier,_ToString)(enumIdentifier enumerationConstant);

#define MU_DEFINE_ENUM_2_WITHOUT_INVALID(enumIdentifier, ... ) typedef enum MU_C2(enumIdentifier, _TAG) {MU_FOR_EACH_2(MU_DEFINE_ENUMERATION_CONSTANT_2, __VA_ARGS__)} enumIdentifier; \
    MU_DECLARE_ENUM_STRINGS_2(enumIdentifier, __VA_ARGS__)

// this macro is a wrapper on top of MU_DEFINE_ENUM, adding an _INVALID value as the first enum value in the enum
#define MU_DEFINE_ENUM_2(enumName, ...) \
    MU_DEFINE_ENUM_2_WITHOUT_INVALID(enumName, MU_C2(enumName, _INVALID), (int)0xDDDDDDDD, __VA_ARGS__)

typedef struct ENUM_VALUE_AND_STRING_TAG
{
    int value;
    const char* valueAsString;
}ENUM_VALUE_AND_STRING;

#define MU_DEFINE_ENUM_VALUE_AND_STRING(enumerationConstant, constantExpression) {enumerationConstant, MU_TOSTRING(enumerationConstant)},
#define MU_DEFINE_ENUM_STRINGS_2(enumIdentifier, ... ) static const ENUM_VALUE_AND_STRING MU_C2(enumIdentifier, _ValuesAndStrings)[MU_DIV2(MU_COUNT_ARG(__VA_ARGS__))] ={MU_FOR_EACH_2(MU_DEFINE_ENUM_VALUE_AND_STRING, __VA_ARGS__)}; \
const char* MU_C3(MU_, enumIdentifier,_ToString)(enumIdentifier value)                                                                                                                                                       \
{                                                                                                                                                                                                                    \
    for(size_t i=0;i<sizeof(MU_C2(enumIdentifier, _ValuesAndStrings))/sizeof(MU_C2(enumIdentifier, _ValuesAndStrings)[0]);i++)                                                                                             \
    {                                                                                                                                                                                                                \
        if(MU_C2(enumIdentifier, _ValuesAndStrings)[i].value == (int)value)                                                                                                                                             \
        {                                                                                                                                                                                                            \
            return MU_C2(enumIdentifier, _ValuesAndStrings)[i].valueAsString;                                                                                                                                           \
        }                                                                                                                                                                                                            \
    }                                                                                                                                                                                                                \
    return "UNKNOWN";                                                                                                                                                                                                \
}                                                                                                                                                                                                                    \

#define MU_ENUM_TO_STRING_2(enumIdentifier, value) MU_C3(MU_, enumIdentifier,_ToString)(value)

/*PRI_BOOL is the format specifier that prints a bool/_Bool*/
#define PRI_BOOL "s (%d)"

/*MU_BOOL_VALUE is the counterpart of PRI_BOOL*/
#define MU_FALSE_STRING "false"
#define MU_TRUE_STRING "true"
#define MU_BOOL_VALUE(v) MU_FALSE_STRING "\0" MU_TRUE_STRING + ((!!(v))*sizeof(MU_FALSE_STRING)), (v)

/*PRI_TIME_T is to be used with a time_t variable - it produces strings such as "Tue May  4 14:42:17 2021". As per 7.27.3.1 The asctime function of C11 it seems that limiting the output to 24 characters should be safe.*/
#define PRI_TIME_T ".24s"

/*TIME_T_VALUE is the counterpar of PRI_TIME_T in a printf/LogError instruction*/
#define TIME_T_VALUE(t) ctime(&t)

/*PRI_MU_ENUM and MU_ENUM_VALUE/MU_ENUM_VALUE_2 work together as printf format specifier/argument. e.g: printf("enumValue was=%" PRI_MU_ENUM "\n", MU_ENUM_TO_STRING(enumIdentifier, enumValue));*/
#define PRI_MU_ENUM "s%s (%d)"

#define MU_ENUM_VALUE(enumIdentifier, value) "", MU_ENUM_TO_STRING(enumIdentifier, (value)), (int)(value)

#define MU_ENUM_VALUE_2(enumIdentifier, value) "", MU_ENUM_TO_STRING_2(enumIdentifier, (value)), (int)(value)

#define CONVERT_ENUM_VALUE(from, to) \
    case (from): \
        *enum_value_to = (to); \
        return 0; \

#define MU_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO) \
    MU_C4(convert_enum_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO)

// This macro declares an enum conversion function that translates a value from one enum to another
#define MU_DECLARE_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO) \
    int MU_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO)(ENUM_TYPE_FROM enum_value_from, ENUM_TYPE_TO* enum_value_to);

// This macro defines an enum conversion function that translates a value from one enum to another
// It is implemented as a switch statement. This allows for catching multiple from values being in the list also
#define MU_DEFINE_CONVERT_ENUM_WITHOUT_INVALID(ENUM_TYPE_FROM, ENUM_TYPE_TO, ...) \
    int MU_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO)(ENUM_TYPE_FROM enum_value_from, ENUM_TYPE_TO* enum_value_to) \
    { \
        switch (enum_value_from) \
        { \
            default: \
                break; \
            MU_FOR_EACH_2(CONVERT_ENUM_VALUE, __VA_ARGS__) \
        } \
        return MU_FAILURE; \
    }

// This macro simply adds the conversion of the "well known" by now _INVALID enum value
#define MU_DEFINE_CONVERT_ENUM_WITHOUT_VALIDATION(ENUM_TYPE_FROM, ENUM_TYPE_TO, ...) \
    MU_DEFINE_CONVERT_ENUM_WITHOUT_INVALID(ENUM_TYPE_FROM, ENUM_TYPE_TO, MU_C2(ENUM_TYPE_FROM, _INVALID), MU_C2(ENUM_TYPE_TO, _INVALID), __VA_ARGS__)

#define CONSTRUCT_FROM_FAKE_ENUM(from_value, to_value) \
    MU_C3(fake_from_, from_value, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51),

#define CONSTRUCT_FIELD_FROM_FAKE_ENUM(from_value, to_value) \
    int MU_C3(fake_from_, from_value, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51)[(MU_C2(enum_value_typedef_, from_value) == MU_C2(enum_value_typedef_, from_value)) ? 1 : 0];

// This macro adds validation of the fact that the from values count in the list match the count of values in the
// (as opposed to the macro MU_DEFINE_CONVERT_ENUM_WITHOUT_VALIDATION)
// from enum type. It does that by having a special fake enum where all the "from" values are enumerated
// The count check is done by having a zero sized array in a struct if the counts do not match
#define MU_DEFINE_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO, ...) \
    /* This forces matching the values in from to enum values generated with MU_DEFINE_ENUM */ \
    typedef struct MU_C3(fake_check_enum_values_exist_, ENUM_TYPE_FROM, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_TAG) \
    { \
        MU_FOR_EACH_2(CONSTRUCT_FIELD_FROM_FAKE_ENUM, __VA_ARGS__) \
    } MU_C3(fake_check_enum_values_exist_, ENUM_TYPE_FROM, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51); \
    /* Have an enum which has all the "from" values */ \
    /* This enum will have a count */ \
    typedef enum MU_C3(fake_, ENUM_TYPE_FROM, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_TAG) \
    { \
        MU_FOR_EACH_2(CONSTRUCT_FROM_FAKE_ENUM, __VA_ARGS__) \
        MU_C3(fake_, ENUM_TYPE_FROM, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_count) \
    } MU_C3(fake_, ENUM_TYPE_FROM, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51); \
    /* "Compare" the count of the from enum values with the count of the values in "ENUM_TYPE_FROM" */ \
    typedef struct MU_C3(fake_, ENUM_TYPE_FROM, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_struct_TAG) \
    { \
        int MU_C3(fake_, ENUM_TYPE_FROM, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_count_test_array)[((MU_C3(fake_, ENUM_TYPE_FROM, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_count) + 1) == MU_C3(enum_value_metadata_, ENUM_TYPE_FROM, _VALUE_COUNT)) ? 1 : 0]; \
        int dummy; \
    } MU_C3(fake_, ENUM_TYPE_FROM, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_struct); \
    MU_DEFINE_CONVERT_ENUM_WITHOUT_VALIDATION(ENUM_TYPE_FROM, ENUM_TYPE_TO, __VA_ARGS__)

#define MU_DEFINE_STRUCT_FIELD(fieldType, fieldName) fieldType fieldName;

/*MU_DEFINE_STRUCT allows creating a struct typedef based on a list of fields*/
#define MU_DEFINE_STRUCT(structName, ...) typedef struct MU_C2(structName, _TAG) { MU_FOR_EACH_2(MU_DEFINE_STRUCT_FIELD, __VA_ARGS__)} structName;

// this macro allows counting of elements in an array
#define MU_COUNT_ARRAY_ITEMS(A) (sizeof(A)/sizeof((A)[0]))

#ifdef _MSC_VER

#define MU_SUPPRESS_WARNING(warn_no)    \
__pragma(warning(push))                 \
__pragma(warning(disable: warn_no))

/*note: warn_no is not used, but helps in code to have it written down*/
#define MU_UNSUPPRESS_WARNING(warn_no)  \
__pragma(warning(pop))

#else
#define MU_SUPPRESS_WARNING(warn_no)
#define MU_UNSUPPRESS_WARNING(warn_no)
#endif

/*MU_EXPAND and MU_NOEXPAND are macros that work in pairs. Here's a typical usage of MU_IF: MU_IF(SOMETHING, TRUEBRANCH(), FALSEBRANCH())*/
/*if FALSEBRANCH() or TRUEBRANCH() expand to something containing a comma, then MU_IF is unhappy because MU_IF expects exactly 3 token.*/
/*the idea is to hide/grab TRUEBRANCH(), FALSEBRANCH(), stick in MU_NOEXPAND. By the way, MU_NOEXPAND is just a token, not even a macro*/
/*so MU_IF actually expands to MU_NOEXPAND(whaveverTRUEBRANCH/FALSEBRANCHexpandedto). to remove MU_NOEXPAND , MU_EXPAND shall be used*/
/*MU_EXPAND actually concatenates with its argument: MU_EXPAND(x)=> MU_EXPAND_x. it so happens that there*/
/*is a macro called MU_EXPAND_MU_NOEXPAND(...) that expands to __VA_ARGS__, thus stealing TRUE/FALSE branch from under MU_IF*/

/*according to https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=vs-2019 this is where VS 2019 starts (1920)*/
/*this is needed because there is NO /experimental:preprocessor or /Zc:preprocessor for VS 2017, it only exists for C++ compiler... apparently*/
/*and there's an absolute need to compile with 2017 (read: vcredist 2019 not being available in the environment where the resulting compiled code is run)*/
#if _MSC_VER < 1920
/*for anything < VS 2019*/
#define MU_NOEXPAND(...) __VA_ARGS__
#define MU_EXPAND(...) __VA_ARGS__
#else
#define MU_C2_MU_EXPAND_(x,y) x##y
#define MU_C2_MU_EXPAND(x,y) MU_C2_MU_EXPAND_(x,y)
#define MU_EXPAND_MU_NOEXPAND(...) __VA_ARGS__
#define MU_EXPAND(x) MU_C2_MU_EXPAND(MU_EXPAND_,x)
#endif



#ifdef __cplusplus
}
#endif

#endif /*MACRO_UTILS_H*/
