#pragma once

#include "./ckg_types.h"
#include "./ckg_string.h"
//========================== Begin Types ==========================
typedef struct CKG_Error {
    char* file;
    int line;
    char* function;
    char* msg;
} CKG_Error;
//=========================== End Types ===========================


CKG_Error ckg_error_stack[1024];
u32 ckg_error_stack_size;
//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
    CKG_Error ckg_error_create(char* file, int line, char* function, char* message, ...); // should dump the stack tracing where and how
    void ckg_error_dump_stack(); // should dump the stack tracing where and how
    void ckg_error_push(CKG_Error error); // should dump the stack tracing where and how
    void ckg_error_pop(); // should dump the stack tracing where and how
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++


#define ckg_errorable(function, msg, ...) ckg_error_push(ckg_error_create(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)); function; ckg_error_pop()
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++