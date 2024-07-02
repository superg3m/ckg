#include "../ckg_error.h"
#include "../ckg_logger.h"
#include "../ckg_memory.h"
#include <stdarg.h>
#include <windows.h>
#include <DbgHelp.h>

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

#pragma comment(lib, "dbghelp.lib")

#define MAX_FRAMES 62
#define MAX_SYMBOL_NAME 256

void ckg_error_dump_stack() {
    // Initialize the symbols
    if (!SymInitialize(GetCurrentProcess(), NULL, TRUE)) {
        printf("Failed to initialize symbols\n");
        return;
    }

    CKG_LOG_PRINT("------------------ Error Stack Trace ------------------\n");

    void* frames[MAX_FRAMES];
    unsigned short framesCount = CaptureStackBackTrace(0, MAX_FRAMES, frames, NULL);

    SYMBOL_INFO* symbolInfo = (SYMBOL_INFO*)malloc(sizeof(SYMBOL_INFO) + (MAX_SYMBOL_NAME - 1) * sizeof(TCHAR));
    if (symbolInfo == NULL) {
        printf("Failed to allocate memory for SYMBOL_INFO\n");
        SymCleanup(GetCurrentProcess());
        return;
    }
    
    symbolInfo->MaxNameLen = MAX_SYM_NAME;
    symbolInfo->SizeOfStruct = sizeof(SYMBOL_INFO);

    for (unsigned short i = 0; i < framesCount; i++) {
        DWORD64 addr = (DWORD64)frames[i];
        DWORD64 displacement = 0;

        if (SymFromAddr(GetCurrentProcess(), addr, &displacement, symbolInfo)) {
            printf("%p (%s+%llx)\n", (void*)addr, symbolInfo->Name, displacement);
        } else {
            printf("%p (unknown)\n", (void*)addr);
        }
    }

    free(symbolInfo);
    SymCleanup(GetCurrentProcess());
    CKG_LOG_PRINT("------------------ Error Stack Trace End ------------------\n");
}

void ckg_error_dump_stack_temp() {
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
