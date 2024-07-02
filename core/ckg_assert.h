#pragma once

#include "./ckg_types.h"
#include "./ckg_memory.h"
#include "./ckg_logger.h"
#include "./ckg_error.h"

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
    #define ckg_assert_in_macro(expression, message, ...)								                    \
        do {																								\
            if (!(expression))                                                       		               	\
            {                                                                        		               	\
                char buffer[CKG_PLATFORM_CHARACTER_LIMIT];                                                  \
                memory_zero(buffer, CKG_PLATFORM_CHARACTER_LIMIT);                                          \
                sprintf(buffer, "file: %s:%d | Function: %s | %s", __FILE__, __LINE__, __func__, message); 	\
                ckg_error_dump_stack();                                                                     \
                CKG_LOG_FATAL(buffer, ##__VA_ARGS__);                                                       \
                CRASH;                                                                                     	\
            }																								\
        } while (FALSE)

    #define ckg_assert_in_function(expression, message, ...)	                                        \
        do { 													                                        \
            if (!(expression))                          		                                        \
            {                                           		                                        \
                ckg_error_push(ckg_error_create(__FILE__, __LINE__, __func__, message, ##__VA_ARGS__)); \
                ckg_error_dump_stack();                                                                 \
                CKG_LOG_FATAL(message, ##__VA_ARGS__);                                                  \
                CRASH;                                  		                                        \
            }													                                        \
        } while (FALSE)
#else
        #define ckg_assert_in_function(expression, message, ...)
        #define ckg_assert_in_macro(expression, message, ...)
#endif
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++