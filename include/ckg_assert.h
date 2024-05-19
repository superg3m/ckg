#pragma once
/*===========================================================
 * File: ckg_assert.h
 * Date: May 18, 2024
 * Creator: Jovanni Djonaj
===========================================================*/
#include "ckg_memory.h"

//========================== Begin Types ==========================
#define ASSERT_ENABLED TRUE

#define CRASH *((int *)0) = 0
//=========================== End Types ===========================

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
#if ASSERT_ENABLED == TRUE	
	#define ckg_assert(expression, message, ...)		\
		do { 											\
			if (!(expression))                          \
			{                                           \
				fprintf(stderr,message, ##__VA_ARGS__); \
				CRASH;                                  \
			}											\
		} while (FALSE)
#else
		#define ckg_assert(expression, message)
#endif
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++

