#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

//========================== Begin Types ==========================
typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef u8 Boolean;

//=========================== End Types ===========================

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
#define FALSE 0
#define TRUE 1
#define NULLPTR 0
#define PI 3.14159265359

#define stringify(entry) #entry
#define glue(a, b) a##b

#define KiloBytes(value) ((u64)(value) * 1024L)
#define MegaBytes(value) ((u64)KiloBytes(value) * 1024L)
#define GigaBytes(value) ((u64)MegaBytes(value) * 1024L)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP(value, min_value, max_value) (MIN(MAX(value, min_value), max_value))

#define local_persist static
#define internal static

// Date: July 12, 2024
// TODO(Jovanni): Test this to make sure its actually works but it makes sense to me
#define OFFSET_OF(type, member) sizeof((u64)(&(((type*)0)->member)))

#define FIRST_DIGIT(number) ((int)number % 10);

void U32_EndianSwap(u32* number_to_endian_swap);
void U64_EndianSwap(u64* number_to_endian_swap);
#define GET_BIT(number, bit_to_check) ((number & (1 << bit_to_check)) >> bit_to_check)
#define SET_BIT(number, bit_to_set) number |= (1 << bit_to_set);
#define UNSET_BIT(number, bit_to_unset) number &= (~(1 << bit_to_unset));

/**
 * @brief This only works on static arrays not buffers
 * 
 */
#define ArrayCount(array) (sizeof(array) / sizeof(array[0]))

#define PLATFORM_MAX_PATH 256

#if defined(_WIN32)
    #define PLATFORM_WINDOWS
    #define OS_DELIMITER '\\'
    #define CRASH *((int *)0) = 0
#elif defined(__APPLE__)
    #define PLATFORM_APPLE
    #define OS_DELIMITER '/'
    #define CRASH __builtin_trap()
#elif defined(__linux__) || defined(__unix__) || defined(__POSIX__)
    #define PLATFORM_LINUX
    #define OS_DELIMITER '/'
    #define CRASH __builtin_trap()
#else
    #error "Unknown Platform???"
#endif
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++

#if defined(CKG_IMPL)
    void U32_EndianSwap(u32* number_to_endian_swap) {
        u32 temp = *number_to_endian_swap;
        
        u32 b0 = (temp >> 0) & 0xFF;
        u32 b1 = (temp >> 8) & 0xFF;
        u32 b2 = (temp >> 16) & 0xFF;
        u32 b3 = (temp >> 24) & 0xFF;

        *number_to_endian_swap = (b0 << 24)|(b1 << 16)|(b2 << 8)|(b3 << 0);
    } 

    void U64_EndianSwap(u64* number_to_endian_swap) {
        u64 temp = *number_to_endian_swap;
        
        u64 b0 = (temp >> 0) & 0xFF;
        u64 b1 = (temp >> 8) & 0xFF;
        u64 b2 = (temp >> 16) & 0xFF;
        u64 b3 = (temp >> 24) & 0xFF;
        u64 b4 = (temp >> 32) & 0xFF;
        u64 b5 = (temp >> 40) & 0xFF;
        u64 b6 = (temp >> 48) & 0xFF;
        u64 b7 = (temp >> 56) & 0xFF;

        *number_to_endian_swap = (b0 << 56)|
        (b1 << 48)|
        (b2 << 40)|
        (b3 << 32)|
        (b4 << 24)|
        (b5 << 16)|
        (b6 << 8)|
        (b7 << 0);
    }
#endif // CKIT_IMPL