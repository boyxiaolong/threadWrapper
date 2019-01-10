#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string>
#include "newlog.h"
#include <cstdio>
#include <windows.h>
#include <DbgHelp.h>
#include "trace.h"
#pragma comment(lib,"Imagehlp.lib")

namespace game
{

    void printStack1()
    {
        unsigned int   i;
        void         * stack[100];
        unsigned short frames;
        SYMBOL_INFO  * symbol;
        HANDLE         process;

        process = GetCurrentProcess();

        SymInitialize(process, NULL, TRUE);

        frames = CaptureStackBackTrace(0, 6, stack, NULL);
        symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
        symbol->MaxNameLen = 255;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

        for (i = 0; i < frames; i++)
        {
            SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);

            LOG("%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address);
        }

        free(symbol);
    }

}
