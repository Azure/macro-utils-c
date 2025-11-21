# Copilot Instructions for macro-utils-c

## Project Overview
This repository provides advanced C macro utilities for Azure IoT SDKs and other C projects requiring robust macro metaprogramming. It consists of a core macro library (`macro_utils.h`) and a C# code generator that auto-generates complex macro sequences.

## Architecture & Key Components

### Core Macro System
- **`inc/macro_utils/macro_utils.h`**: Main header with hand-written utility macros
- **`inc/macro_utils/macro_utils_generated.h`**: Auto-generated header with repetitive macro sequences (25K+ lines)
- **Code Generator**: `macro_utils_h_generator/` (C# project) regenerates the generated header

### Key Macro Patterns
- **Enum Macros**: `MU_DEFINE_ENUM(NAME, values...)` creates enum + string conversion functions
- **Struct Macros**: `MU_DEFINE_STRUCT(NAME, type1, field1, type2, field2...)` creates typedef structs
- **FOR_EACH Macros**: `MU_FOR_EACH_1_KEEP_1(MACRO, keepValue, list...)` applies macro to each list item
- **Arithmetic**: `MU_INC(x)`, `MU_DEC(x)`, `MU_COUNT_ARG(...)` for compile-time calculations

## Developer Workflows

### Build & Test
- **Standard Build**: By default, use the existing `cmake/` directory for builds. Run `cmake .. && cmake --build . --target install` from the `cmake/` directory
- **Alternative Build**: Can create a new `build/` directory if needed, but `cmake/` is the conventional location
- **Enable Tests**: Set `run_int_tests=ON` in CMake configuration
- **Test Structure**: Each macro category has dedicated test files (e.g., `mu_define_enum_test.c`)

### Regenerating Macros
- **Windows Only**: Open `macro_utils_h_generator/macro_utils_h_generator.sln` in Visual Studio
- **Run Generator**: Press F5 to execute. Updates `inc/macro_utils/macro_utils_generated.h`
- **Template Logic**: Modify `macro_utils_generated.tt` (T4 template) and `program.cs` for new patterns
- **Critical Limits**: `nArithmetic=2048` and `nMacroParameters=140` control generation scope
- **No CI Integration**: Manual regeneration required after template changes

### Integration Usage
```c
#include "macro_utils/macro_utils.h"

// Define enum with automatic string conversion
MU_DEFINE_ENUM(STATUS, SUCCESS, FAILURE, TIMEOUT);
MU_DEFINE_ENUM_STRINGS(STATUS, SUCCESS, FAILURE, TIMEOUT);

// Define struct from field list
MU_DEFINE_STRUCT(CONFIG, int, port, char*, hostname);

// Use enum-to-string conversion
const char* status_str = MU_ENUM_TO_STRING(STATUS, SUCCESS);
```

## Project-Specific Conventions

### Macro Naming
- **MU_** prefix for all public macros
- **DEFINE** for type creation, **FOR_EACH** for iteration, **COUNT** for arithmetic
- Test macros follow pattern: `<feature>_test.c/.h`

### Code Generation Limits
- **140 macro parameters** maximum (C99 limit is 127, extended for upstream projects)
- **2048 arithmetic operations** supported (MU_INC/MU_DEC up to this limit)
- **Generated file size**: ~25K lines in `macro_utils_generated.h`

### Test Patterns
- Each test defines value lists as macros, then uses `MU_FOR_EACH_*` to generate test variables
- Tests validate generated types compile and produce expected runtime behavior
- Use `POOR_MANS_ASSERT` for validation (custom assertion macro in `test_helper.h`)
- **AAA Pattern**: Tests follow Arrange/Act/Assert adapted for macro testing:
  - **Arrange**: Define test data as macros (e.g., `#define LIST_3_ELEMENTS 41, 42, 43`)
  - **Act**: Apply macros at compile-time to generate variables/types (e.g., `MU_FOR_EACH_1_KEEP_1(MY_MACRO_X, 5, LIST_3_ELEMENTS)`)
  - **Assert**: Runtime verification that generated code behaves correctly (e.g., `POOR_MANS_ASSERT(x_value_1_41 == 5)`)

### Assertion Macros
- **`POOR_MANS_ASSERT(condition)`**: Runtime assertion that prints failure location and returns line number on failure
- **`MU_STATIC_ASSERT(condition)`**: Compile-time assertion using array size trick - fails compilation if condition is false
- **Self-contained testing**: No external test framework dependencies - all assertions are custom-built for macro validation

## External Dependencies
For build/test/pipeline conventions, refer to #file:../deps/c-build-tools/.github/copilot-instructions.md. This project inherits all build infrastructure from c-build-tools.

**IMPORTANT**: All code changes must follow the comprehensive coding standards defined in #file:../deps/c-build-tools/.github/general_coding_instructions.md, including:
- Function naming conventions (snake_case, module prefixes, internal function patterns)
- Parameter validation rules and error handling patterns  
- Variable naming and result variable conventions
- Header inclusion order and memory management requirements
- Requirements traceability system (SRS/Codes_SRS/Tests_SRS patterns)
- Async callback patterns and goto usage rules
- Indentation, formatting, and code structure guidelines

## Critical Files
- `inc/macro_utils/macro_utils.h`: Core macro definitions
- `macro_utils_h_generator/macro_utils_generated.tt`: T4 template for code generation
- `tests/`: Comprehensive macro validation tests
- `CMakeLists.txt`: Interface library configuration for consumption by other projects
