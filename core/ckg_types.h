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

#define stringify(entry) #entry
#define glue(a, b) a##b

#define KiloBytes(value) ((u64)(value) * 1024L)
#define MegaBytes(value) ((u64)KiloBytes(value) * 1024L)
#define GigaBytes(value) ((u64)MegaBytes(value) * 1024L)

#define local_persist static
#define internal static

/**
 * @brief This only works on static arrays not buffers
 * 
 */
#define ArrayCount(array) (sizeof(array) / sizeof(array[0]))

#define CRASH *((int *)0) = 0
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++