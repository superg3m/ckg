#include "../ckg_error.h"
#include "../ckg_logger.h"
#include "../ckg_memory.h"
#include <stdarg.h>

#define CKG_ERROR_OUT_MESSAGE_LIMIT 2048
 
CKG_Error ckg_error_create(char* file, int line, char* function, char* message, ...) {
    CKG_Error ret;

    va_list va_arguments;

    char out_message[CKG_ERROR_OUT_MESSAGE_LIMIT];
    ckg_memory_zero(out_message, CKG_ERROR_OUT_MESSAGE_LIMIT);
 
    va_start(va_arguments, message);
    vsnprintf(out_message, CKG_ERROR_OUT_MESSAGE_LIMIT, message, va_arguments);
    va_end(va_arguments);

    ret.file = file;
    ret.function = function;
    ret.line = line;
    ret.msg = ckg_string_allocate(out_message);

    return ret;
}

internal void ckg_error_free(CKG_Error error) {
    ckg_memory_free(error.msg);
}

internal void ckg_error_print(CKG_Error error) {
    CKG_LOG_PRINT("     file: %s:%d\n", error.file, error.line);
    CKG_LOG_PRINT("     function: %s\n", error.function);
    CKG_LOG_PRINT("     Error Message: %s\n", error.msg);
}

void ckg_error_dump_stack() {
    CKG_LOG_PRINT("------------------ Error Stack Trace ------------------\n");
    for (u32 i = 0; i < ckg_error_stack_size; i++) {
        CKG_LOG_PRINT(" Stack Level: %d\n", i + 1);
        ckg_error_print(ckg_error_stack[i]);
    }
    CKG_LOG_PRINT("------------------ Error Stack Trace End ------------------\n");
}

void ckg_error_push(CKG_Error error) {
    ckg_error_stack[ckg_error_stack_size++] = error;
}

void ckg_error_pop() {
    ckg_error_free(ckg_error_stack[ckg_error_stack_size--]);
}
