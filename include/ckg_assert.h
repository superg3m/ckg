#pragma once
/*===========================================================
 * File: ckg_assert_in_function.h
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

	#define ckg_assert_in_macro(buffer, buffer_size, expression, message, ...)								\
		do {																								\
			if (!(expression))                                                       		               	\
			{                                                                        		               	\
				memory_zero(buffer, buffer_size);                                             				\
				sprintf(buffer, "file: %s:%d | Function: %s | %s", __FILE__, __LINE__, __func__, message); 	\
				fprintf(stderr, buffer, ##__VA_ARGS__);                                             \
				CRASH;                                                                                     	\
			}																								\
		} while (FALSE)

	#define ckg_assert_in_function(expression, message, ...)	\
		do { 													\
			if (!(expression))                          		\
			{                                           		\
				fprintf(stderr, message, ##__VA_ARGS__); 		\
				CRASH;                                  		\
			}													\
		} while (FALSE)

#else
		#define ckg_assert_in_function(expression, message)
#endif
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++

