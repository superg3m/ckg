#include "../ckg_error.h"
#include "../ckg_logger.h"
#include "../ckg_memory.h"
#include <stdarg.h>

#define CKG_ERROR_OUT_MESSAGE_LIMIT 2048
 
CKG_Error ckg_error_create(char* file, int line, char* function) {
    CKG_Error ret;

    ret.file = file;
    ret.function = function;
    ret.line = line;

    return ret;
}

internal void ckg_error_print(CKG_Error error) {
    CKG_LOG_PRINT("     file: %s:%d\n", error.file, error.line);
    CKG_LOG_PRINT("     function: %s\n", error.function);
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
    ckg_error_stack_size--;
}
