#pragma once
/*===========================================================
 * File: core_types.h
 * Date: April 23, 2024
 * Creator: Jovanni Djonaj
===========================================================*/
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

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
#define TRUE 1
#define FALSE 0
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
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++