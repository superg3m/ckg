#include "../ckg_error.h"
#include "../ckg_logger.h"
#include "../ckg_memory.h"
#include <stdarg.h>
#include <windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp")

void ckg_error_dump_stack() {
    CKG_LOG_PRINT("------------------ Error Stack Trace ------------------\n");
    // Date: July 02, 2024
    // TODO(Jovanni): This only works for windows and when debug symbols are compiled into the program
    void *stack[100];
    unsigned short number_of_captured_frames;
    SYMBOL_INFO *symbol;
    HANDLE process;

    process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);

    number_of_captured_frames = CaptureStackBackTrace(0, 100, stack, NULL);
    symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
    symbol->MaxNameLen = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    int count = 0;
    for (int i = number_of_captured_frames - 4; i > 0; i--) {
        DWORD64 displacement = 0;
        if (SymFromAddr(process, (DWORD64)(stack[i]), &displacement, symbol)) {
            DWORD displacementLine = 0;
            IMAGEHLP_LINE64 line;
            line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
            if (SymGetLineFromAddr64(process, (DWORD64)(stack[i]), &displacementLine, &line)) {
                printf("%d: %s - %s:%d\n", count, symbol->Name, line.FileName, line.LineNumber);
            } else {
                printf("%d: %s\n", count, symbol->Name, symbol->Address);
            }
        }
        count++;
    }

    free(symbol);
    CKG_LOG_PRINT("------------------ Error Stack Trace End ------------------\n");
}