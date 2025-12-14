# CKG Core Library

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This header file, `ckg.h`, provides a foundational set of cross-platform utilities and data structures in C. It aims to simplify common programming tasks and promote code reusability. The library is designed to be modular, allowing you to include only the functionality you need.

**Builds using `c_build` with `cl`/`gcc`/`g++` and on Ubuntu (WSL).**
**Last Updated: 05/19/2025**

## CKG's Core Thesis
-   The point of the ckit granular (ckg) is building out everything at a granular level.
    -   Using this small library to build out [CKIT](https://github.com/superg3m/ckit) (A much more sophisticated C library build).
-   This library will be completely cross-platform.
-   Collection of tools, data structures, and algorithms that I find useful.

## Features
The CKG Core Library includes the following modules:
- **Types (`CKG_INCLUDE_TYPES`):** Defines fundamental types
- **Logger (`CKG_INCLUDE_LOGGER`):** Provides a simple logging mechanism with different severity levels (Fatal, Error, Warn, Debug, Success, Print) and color-coded output for easier debugging.
- **Assert (`CKG_INCLUDE_ASSERT`):** Offers assertion macros (`ckg_assert`, `ckg_assert_msg`) that can be enabled or disabled globally to help catch programming errors during development.
- **Errors (`CKG_INCLUDE_ERRORS`):** Includes a function to get a string representation of an error code (`ckg_error_str`).
- **Memory (`CKG_INCLUDE_MEMORY`):** Supports custom allocators.
- **Arena (`CKG_INCLUDE_ARENA`):** Implements an arena allocator for efficient allocation.
- **String (`CKG_INCLUDE_STRING`):** Provides a set of string manipulation functions including string views.
- **Char (`CKG_INCLUDE_CHAR`):** Offers basic character classification macros (e.g., `ckg_char_is_digit`, `ckg_char_is_upper`) and functions (`ckg_char_is_alpha`, `ckg_char_is_alpha_numeric`).
- **Collections (`CKG_INCLUDE_COLLECTIONS`):** Includes implementations for dynamic arrays, stacks, circular buffers, and doubly-linked lists.
- **Serialization (`CKG_INCLUDE_SERIALIZATION`):** Offers basic functions for serializing and deserializing collections (Vectors, Stacks, Ring Buffers, Linked Lists).
- **IO (`CKG_INCLUDE_IO`):** Provides basic input/output utilities
- **OS (`CKG_INCLUDE_OS`):** Includes functions for operating system-level tasks, such as loading dynamic link libraries (DLLs/shared libraries) (`ckg_io_load_dll`).

## Key Notes
-   `[OPTIONAL]` indicates that you can pass `NULLPTR` for that parameter.

## How to build using [c-build](https://github.com/superg3m/c-build)
1.  `./bootstrap.ps1`
2.  `./build.ps1` or `./build.ps1 -debug`
3.  `./run.ps1` or `./run.ps1 -debug`
4.  `./debug.ps1`

## Goals
-   [ ] hashmap needs to not have any UB!
-   [ ] make all the `u8*` to `void*` so I don't accidentally break strict aliasing.
-   [ ] The solution to strict aliasing is just memory copy.

### Key
-   '[x]': Finished
-   '[/]': Started working on it
-   '[ ]': Haven't started working on it

## Usage
#define CKG_IMPL
#include <ckg.h>

## Dev Notes (For me)
-   Write a bunch more tests!
-   `ckg_printf()`
-   `thead_local` (Experiment with this more)

## License
This library is licensed under the [MIT License](https://opensource.org/licenses/MIT). See the `LICENSE` file for more information.