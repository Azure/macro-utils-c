// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MACRO_UTILS_H
#define MACRO_UTILS_H

#include "macro_utils/macro_utils_generated.h"

#ifdef __cplusplus
#include <cstring>
#include <cstddef>
#include <ctime>
#include <cinttypes>
extern "C" {
#else
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <inttypes.h>
#endif

#if (defined OPTIMIZE_RETURN_CODES)
    #define MU_FAILURE 1
#else
    #define MU_FAILURE __LINE__
#endif

#ifdef _MSC_VER
    #define MU_UNUSED_VAR __pragma(warning(suppress:4189))
#elif __GNUC__
    #define MU_UNUSED_VAR __attribute__((unused))
#else
// Unknown compiler
#endif

/*"pointer or NULL" macro - because when printf-ing arguments NULL is not valid for %s (section 7.1.4 of C11 standard) */
#define MU_P_OR_NULL(p) (((p)!=NULL)?(p):"NULL")
#define MU_WP_OR_NULL(p) (((p)!=NULL)?(p):L"NULL")

#define MU_TOSTRING_(x) #x
#define MU_TOSTRING(x) MU_TOSTRING_(x)

#define MU_TOWSTRING_(x) L ## #x
#define MU_TOWSTRING(x) MU_TOWSTRING_(x)

/*macro that expands to a printf format specifier that can be used to nice print filesizes. It produces output like 45 B (45) or 1.9 GB (2040109488) or 2 KB (2050).*/
#define PRI_KB "" PRIu64 "%s%." PRIu64 " %s"
#define PRI_1KB (1024)
#define PRI_1MB (PRI_1KB*PRI_1KB)
#define PRI_1GB (PRI_1MB*PRI_1KB)

/*below macro produces the integer part of the value (x) in KB, MB or GB*/
#define KB_VALUE_INT(x) (          \
    (x)>=PRI_1GB?                  \
        ((x)/PRI_1GB)              \
    :                              \
        (x)>=PRI_1MB?              \
            ((x)/PRI_1MB)          \
        :                          \
            (x)>=PRI_1KB?          \
                ((x)/PRI_1KB)      \
            :                      \
                (x)                \
)


/*below macro produces the first digit of the fractional part of the value (x) in KB, MB or GB*/
#define KB_FIRST_FRACTIONAL_DIGIT(x) (          \
    (x)>=PRI_1GB?                               \
        ((((x)*10)/PRI_1GB)%10)                 \
    :                                           \
        (x)>=PRI_1MB?                           \
            ((((x)*10)/PRI_1MB)%10)             \
        :                                       \
            (x)>=PRI_1KB?                       \
                ((((x)*10)/PRI_1KB)%10)         \
            :                                   \
                0                               \
)

/*this macro produces the fractional dot IF the first fractional digit is not 0*/
#define KB_FRACTIONAL_DOT(x) ((KB_FIRST_FRACTIONAL_DIGIT(x)>0)?".":"")

/*below macro produces the unit for measurement for (x)*/
#define KB_UNIT(x) (                            \
    (x)>=PRI_1GB?                               \
        "GB"                                    \
    :                                           \
        (x)>=PRI_1MB?                           \
            "MB"                                \
        :                                       \
            (x)>=PRI_1KB?                       \
                "KB"                            \
            :                                   \
                "B"                             \
)

/*KB_VALUE is the counterpart of PRI_KB.*/
#define KB_VALUE(x) KB_VALUE_INT(x), KB_FRACTIONAL_DOT(x), KB_FIRST_FRACTIONAL_DIGIT(x), KB_UNIT(x)

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

#define MU_DEFINE_ENUM_WITHOUT_INVALID_TYPEDEF(enumName, ... ) \
    typedef enum MU_C2(enumName, _TAG) { MU_FOR_EACH_1(MU_DEFINE_ENUMERATION_CONSTANT, __VA_ARGS__)} enumName;

#define MU_DECLARE_ENUM_TO_STRING(enumName, ...) \
    const char* MU_C3(MU_, enumName, _ToString)(enumName value);

#define MU_DEFINE_ENUM_WITHOUT_INVALID_TO_STRING(enumName, ... )     \
    typedef enum MU_C3(enum_value_metadata_, enumName, _TAG) { MU_FOR_EACH_1(MU_DEFINE_METADATA_ENUMERATION_VALUE, __VA_ARGS__) MU_C3(enum_value_metadata_, enumName, _VALUE_COUNT) = MU_COUNT_ARG(__VA_ARGS__)} MU_C2(enum_value_metadata_, enumName); \
    MU_DECLARE_ENUM_TO_STRING(enumName, __VA_ARGS__) \

/*MU_DEFINE_ENUM_WITHOUT_INVALID goes to header*/
#define MU_DEFINE_ENUM_WITHOUT_INVALID(enumName, ...) \
    MU_DEFINE_ENUM_WITHOUT_INVALID_TYPEDEF(enumName, __VA_ARGS__) \
    MU_DEFINE_ENUM_WITHOUT_INVALID_TO_STRING(enumName, __VA_ARGS__)

// this macro is a wrapper on top of MU_DEFINE_ENUM_WITHOUT_INVALID, adding an _INVALID value as the first enum value in the enum
#define MU_DEFINE_ENUM(enumName, ...) \
    MU_DEFINE_ENUM_WITHOUT_INVALID(enumName, MU_C2(enumName, _INVALID), __VA_ARGS__)

#define MU_INTERNAL_DEFINE_ENUM_VAR(enumName, enumValue) \
    static enumName MU_C2(my_, enumValue);

#define MU_INTERNAL_ASSIGN_ENUM_VALUE(argCount, enumValue) \
    switch (MU_C2(enum_value_has_equal_, argCount)) \
    { \
        default: \
        case MU_ENUM_VALUE_CONTAINS_EQUAL_UNKNOWN: \
            if (strchr(MU_TOSTRING(MU_C2(my_, enumValue)), '=') != NULL) \
            { \
                MU_C2(enum_value_has_equal_, argCount) = MU_ENUM_VALUE_CONTAINS_EQUAL_YES; \
                has_equal = 1; \
            } \
            else \
            { \
                MU_C2(enum_value_has_equal_, argCount) = MU_ENUM_VALUE_CONTAINS_EQUAL_NO; \
                has_equal = 0; \
            } \
            break; \
        case MU_ENUM_VALUE_CONTAINS_EQUAL_YES: \
            has_equal = 1; \
            break; \
        case MU_ENUM_VALUE_CONTAINS_EQUAL_NO: \
            has_equal = 0; \
            break; \
    } \
    if ((MU_C2(my_, enumValue)) == 0) \
    { \
        /* it is zero, either because not filled in or because it was explicit zero */ \
        /* if it has an equal it cannot be implicit */ \
        if (has_equal) \
        { \
            /* explicit zero */ \
            current_enum_value = 0; \
        } \
        else \
        { \
            current_enum_value = previous_enum_value + 1; \
        } \
    } \
    else \
    { \
        /* non zero value, thus it was filled in */ \
        current_enum_value = MU_C2(my_, enumValue); \
    } \
    previous_enum_value = current_enum_value; \
    if (current_enum_value == value) \
    { \
        static char result [] = MU_TOSTRING(enumValue); \
        static int visited; /*initialized to 0 by "static"*/ \
        if(visited == 0) \
        { \
            result[strspn(result, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_")] = '\0'; \
            visited = 1; \
        } \
        return result; \
    }

#define MU_DEFINE_ENUMERATION_CONSTANT_AS_WIDESTRING(x) MU_C2(L, MU_TOSTRING(x)) ,
#define MU_DEFINE_ENUMERATION_CONSTANT_AS_STRING(x) MU_TOSTRING(x) ,

typedef enum MU_ENUM_VALUE_CONTAINS_EQUAL_TAG
{
    MU_ENUM_VALUE_CONTAINS_EQUAL_UNKNOWN,
    MU_ENUM_VALUE_CONTAINS_EQUAL_YES,
    MU_ENUM_VALUE_CONTAINS_EQUAL_NO
} MU_ENUM_VALUE_CONTAINS_EQUAL;

// variable definition indicating if an enum value label contains or not equal
#define MU_INTERNAL_DEFINE_ENUM_HAS_EQ_VAR(argCount, enumValue) \
    static MU_ENUM_VALUE_CONTAINS_EQUAL MU_C2(enum_value_has_equal_, argCount) = MU_ENUM_VALUE_CONTAINS_EQUAL_UNKNOWN; \

// This is the bulk of the _ToString for an enum
// The algorithm is:
// - Go through each enum value
//   - Determine if it contains an equal by searching '=' in the enum value string
//     This value is cached. Threading is not taken into account, if a dirty read happens and an unknown value is obtained
//     the code will simply take the worse case and take a performance hit in recomputing whether an equal is in the string
//   - Determine the actual value of the enum value that we need to compare against:
//     - Have a fake variable that is either initialized because there is an equal in the enum label or it is initialized to 0
//       because the fake variables are static
//     - If the enum value contains an equal then take as current enum value whatever is in the fake variable
//     - If the enum value does not contain an equal then compute the current enum value as the previous enum value plus 1
//   - If the currently computed enum value matches the value requested to be stringified by the user then return the string to the user
#define MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID_COMMON_CODE(enumName, ...) \
    { \
        int has_equal = 0; \
        MU_FOR_EACH_1_KEEP_1(MU_INTERNAL_DEFINE_ENUM_VAR, enumName, __VA_ARGS__) \
        MU_FOR_EACH_1_COUNTED(MU_INTERNAL_DEFINE_ENUM_HAS_EQ_VAR, __VA_ARGS__) \
        int current_enum_value = -1; \
        int previous_enum_value = -1; \
        MU_FOR_EACH_1_COUNTED(MU_INTERNAL_ASSIGN_ENUM_VALUE, __VA_ARGS__) \
        return "UNKNOWN"; \
    }

/*MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID goes to .c*/
#define MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID(enumName, ...) \
    const char* MU_C3(MU_, enumName, _ToString)(enumName value) \
    MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID_COMMON_CODE(enumName, __VA_ARGS__)

// this macro is a wrapper on top of MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID, adding an _INVALID value as the first enum value in the enum
#define MU_DEFINE_ENUM_STRINGS(enumName, ...) \
    MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID(enumName, MU_C2(enumName, _INVALID), __VA_ARGS__)

#define MU_DEFINE_LOCAL_ENUM_WITHOUT_INVALID(enumName, ...) \
    typedef enum MU_C2(enumName, _TAG) { MU_FOR_EACH_1(MU_DEFINE_ENUMERATION_CONSTANT, __VA_ARGS__)} enumName; \
    static const char* MU_C3(MU_, enumName, _ToString)(enumName value) \
    MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID_COMMON_CODE(enumName, __VA_ARGS__)

// this macro is a wrapper on top of MU_DEFINE_LOCAL_ENUM_WITHOUT_INVALID, adding an _INVALID value as the first enum value in the enum
#define MU_DEFINE_LOCAL_ENUM(enumName, ...) \
    MU_DEFINE_LOCAL_ENUM_WITHOUT_INVALID(enumName, MU_C2(enumName, _INVALID), __VA_ARGS__)

// this macro returns the number of enum values (taking into account that an invalid value is generated)
#define MU_ENUM_VALUE_COUNT(...) (MU_COUNT_ARG(__VA_ARGS__) + 1)
#define MU_ENUM_VALUE_COUNT_WITHOUT_INVALID(...) (MU_COUNT_ARG(__VA_ARGS__))

#define MU_ENUM_TO_STRING(enumName, value) \
    MU_C3(MU_, enumName, _ToString)(value)

#define MU_STRING_TO_ENUM(stringValue, enumName, addressOfEnumVariable) MU_C2(enumName, _FromString)(stringValue, addressOfEnumVariable)

#define MU_EMPTY()
#define MACRO_UTILS_DELAY(id) id MU_EMPTY MU_LPAREN )

#define MU_DECLARE_ENUM_STRINGS(enumIdentifier, ...) extern const char* MU_C3(MU_, enumIdentifier,_ToString)(enumIdentifier enumerationConstant);

/*PRI_BOOL is the format specifier that prints a bool/_Bool*/
#define PRI_BOOL "s (%d)"

/*MU_BOOL_VALUE is the counterpart of PRI_BOOL*/
#define MU_FALSE_STRING "false"
#define MU_TRUE_STRING "true"
#define MU_BOOL_VALUE(v) &(MU_FALSE_STRING "\0" MU_TRUE_STRING[((!!(v))*sizeof(MU_FALSE_STRING))]), (v)

/*PRI_TIME_T is to be used with a time_t variable - it produces strings such as "Tue May  4 14:42:17 2021". As per 7.27.3.1 The asctime function of C11 it seems that limiting the output to 24 characters should be safe.*/
#define PRI_TIME_T ".24s"

/*TIME_T_VALUE is the counterpar of PRI_TIME_T in a printf/LogError instruction*/
#define TIME_T_VALUE(t) ctime(&t)

/*PRI_MU_ENUM and MU_ENUM_VALUE work together as printf format specifier/argument. e.g: printf("enumValue was=%" PRI_MU_ENUM "\n", MU_ENUM_TO_STRING(enumIdentifier, enumValue));*/
#define PRI_MU_ENUM "s%s (%d)"

#define MU_ENUM_VALUE(enumIdentifier, value) "", MU_ENUM_TO_STRING(enumIdentifier, (value)), (int)(value)

#define CONVERT_ENUM_VALUE(from, to) \
    case (from): \
        *enum_value_to = (to); \
        return 0; \

#define MU_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO) \
    MU_C4(convert_enum_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO)

#define MU_CONVERT_ENUM_WITH_DEFAULT(ENUM_TYPE_FROM, ENUM_TYPE_TO) MU_C5(convert_enum_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO, _with_default)

// This macro declares an enum conversion function that translates a value from one enum to another
#define MU_DECLARE_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO) \
    int MU_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO)(ENUM_TYPE_FROM enum_value_from, ENUM_TYPE_TO* enum_value_to);

// This macro declares an enum conversion function that translates a value from one enum to another with a default value
#define MU_DECLARE_CONVERT_ENUM_WITH_DEFAULT(ENUM_TYPE_FROM, ENUM_TYPE_TO) \
    ENUM_TYPE_TO MU_CONVERT_ENUM_WITH_DEFAULT(ENUM_TYPE_FROM, ENUM_TYPE_TO)(ENUM_TYPE_FROM from);

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
    MU_C5(fake_from_, from_value, _, to_value, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51),

#define CONSTRUCT_FIELD_FROM_FAKE_ENUM(from_value, to_value) \
    int MU_C5(fake_from_, from_value, _, to_value, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51)[(MU_C2(enum_value_typedef_, from_value) == MU_C2(enum_value_typedef_, from_value)) ? 1 : 0];

// This macro adds validation of the fact that the from values count in the list match the count of values in the from enum type
// (as opposed to the macro MU_DEFINE_CONVERT_ENUM_WITHOUT_VALIDATION). It does that by having a special fake enum where all the "from" values are enumerated
// The count check is done by having a zero sized array in a struct if the counts do not match
#define MU_DEFINE_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO, ...) \
    /* This forces matching the values in from to enum values generated with MU_DEFINE_ENUM */ \
    typedef struct MU_C5(fake_check_enum_values_exist_, ENUM_TYPE_FROM,_, ENUM_TYPE_TO, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_TAG) \
    { \
        MU_FOR_EACH_2(CONSTRUCT_FIELD_FROM_FAKE_ENUM, __VA_ARGS__) \
    } MU_C5(fake_check_enum_values_exist_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51); \
    /* Have an enum which has all the "from" values */ \
    /* This enum will have a count */ \
    typedef enum MU_C5(fake_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_TAG) \
    { \
        MU_FOR_EACH_2(CONSTRUCT_FROM_FAKE_ENUM, __VA_ARGS__) \
        MU_C5(fake_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_count) \
    } MU_C5(fake_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51); \
    /* "Compare" the count of the from enum values with the count of the values in "ENUM_TYPE_FROM" */ \
    typedef struct MU_C5(fake_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_struct_TAG) \
    { \
        int MU_C5(fake_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_count_test_array)[((MU_C5(fake_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_count) + 1) == MU_C3(enum_value_metadata_, ENUM_TYPE_FROM, _VALUE_COUNT)) ? 1 : 0]; \
        int dummy; \
    } MU_C5(fake_, ENUM_TYPE_FROM, _, ENUM_TYPE_TO, _C0FB3709_EDE8_4288_8F70_FDDB5D8D7A51_struct); \
    MU_DEFINE_CONVERT_ENUM_WITHOUT_VALIDATION(ENUM_TYPE_FROM, ENUM_TYPE_TO, __VA_ARGS__)

// Internal macro which adds a wrapper around the convert enum which will handle the return code and translate to a default
#define MU_DEFINE_CONVERT_ENUM_WITH_DEFAULT_INTERNAL(ERROR_LOGGING_FUNCTION, ENUM_TYPE_FROM, ENUM_TYPE_TO, DEFAULT, ...) \
    ENUM_TYPE_TO MU_CONVERT_ENUM_WITH_DEFAULT(ENUM_TYPE_FROM, ENUM_TYPE_TO)(ENUM_TYPE_FROM from) \
    { \
        ENUM_TYPE_TO result; \
        if (MU_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO)(from, &result) != 0) \
        { \
            ERROR_LOGGING_FUNCTION("Encountered unknown enum value %" PRI_MU_ENUM ", treat as %" PRI_MU_ENUM, \
                MU_ENUM_VALUE(ENUM_TYPE_FROM, from), MU_ENUM_VALUE(ENUM_TYPE_TO, DEFAULT)); \
            result = DEFAULT; \
        } \
        return result; \
    }

// Defines a conversion where unknown values are converted to DEFAULT
#define MU_DEFINE_CONVERT_ENUM_WITH_DEFAULT(ERROR_LOGGING_FUNCTION, ENUM_TYPE_FROM, ENUM_TYPE_TO, DEFAULT, ...) \
    MU_DEFINE_CONVERT_ENUM(ENUM_TYPE_FROM, ENUM_TYPE_TO, __VA_ARGS__) \
    MU_DEFINE_CONVERT_ENUM_WITH_DEFAULT_INTERNAL(ERROR_LOGGING_FUNCTION, ENUM_TYPE_FROM, ENUM_TYPE_TO, DEFAULT, __VA_ARGS__) \

// Defines a conversion where unknown values are converted to DEFAULT
// using the without validation version so enum values can be skipped
#define MU_DEFINE_CONVERT_ENUM_WITH_DEFAULT_WITHOUT_VALIDATION(ERROR_LOGGING_FUNCTION, ENUM_TYPE_FROM, ENUM_TYPE_TO, DEFAULT, ...) \
    MU_DEFINE_CONVERT_ENUM_WITHOUT_VALIDATION(ENUM_TYPE_FROM, ENUM_TYPE_TO, __VA_ARGS__) \
    MU_DEFINE_CONVERT_ENUM_WITH_DEFAULT_INTERNAL(ERROR_LOGGING_FUNCTION, ENUM_TYPE_FROM, ENUM_TYPE_TO, DEFAULT, __VA_ARGS__) \

// Defines a conversion where unknown values are converted to DEFAULT and the _INVALID value (0) is treated as DEFAULT
#define MU_DEFINE_CONVERT_ENUM_WITH_DEFAULT_WITHOUT_INVALID(ERROR_LOGGING_FUNCTION, ENUM_TYPE_FROM, ENUM_TYPE_TO, DEFAULT, ...) \
    MU_DEFINE_CONVERT_ENUM_WITHOUT_INVALID(ENUM_TYPE_FROM, ENUM_TYPE_TO, __VA_ARGS__) \
    MU_DEFINE_CONVERT_ENUM_WITH_DEFAULT_INTERNAL(ERROR_LOGGING_FUNCTION, ENUM_TYPE_FROM, ENUM_TYPE_TO, DEFAULT, __VA_ARGS__) \

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
#if defined(_MSC_VER) && (_MSC_VER < 1920 )
/*for anything < VS 2019*/
#define MU_NOEXPAND(...) __VA_ARGS__
#define MU_EXPAND(...) __VA_ARGS__
#else
#define MU_C2_MU_EXPAND_(x,y) x##y
#define MU_C2_MU_EXPAND(x,y) MU_C2_MU_EXPAND_(x,y)
#define MU_EXPAND_MU_NOEXPAND(...) __VA_ARGS__
#define MU_EXPAND(x) MU_C2_MU_EXPAND(MU_EXPAND_,x)
#endif


#define MU_IS_VALUE_EQUAL_ONE_OF_VALUES(VALUE, ONE_OF_VALUES) +((VALUE)==(ONE_OF_VALUES))

/*evaluates to 0 or 1*/
#define MU_IS_NONE_OF(VALUE, ...) ( MU_FOR_EACH_1_KEEP_1(MU_IS_VALUE_EQUAL_ONE_OF_VALUES, (VALUE), __VA_ARGS__) == 0)

#define MU_IS_NONE_OF_EXPRESSION_BUILDER(N, ...) MU_IS_NONE_OF(N, __VA_ARGS__) ? (N) :

#define MU_DIFFERENT(...) (MU_DO(MU_COUNT_ARG(__VA_ARGS__), MU_IS_NONE_OF_EXPRESSION_BUILDER, __VA_ARGS__)  (-1) ) /*-1 is the last ?: ternary third operator, and it is never an output of this macro*/

#define MU_STATIC_ASSERT_EX(CONDITION, LINE) typedef int MU_UNUSED_VAR MU_C3(assertion_line_, LINE, _failed)[(CONDITION) ? 1 : -1];

#define MU_STATIC_ASSERT(CONDITION) MU_STATIC_ASSERT_EX(CONDITION, __LINE__)

#if defined _MSC_VER
#define MU_FUNCDNAME __FUNCDNAME__
#else
#define MU_FUNCDNAME __func__
#endif


#ifdef __cplusplus
}
#endif

#endif /*MACRO_UTILS_H*/
