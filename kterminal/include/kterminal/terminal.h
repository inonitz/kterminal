#ifndef __KERNEL_TERMINAL_EMULATOR_TERMINAL_STRUCTURE_DEFINITION__
#define __KERNEL_TERMINAL_EMULATOR_TERMINAL_STRUCTURE_DEFINITION__
#include <kterminal/kterm_api.h>
#include <kterminal/types.h>


KTERM_API void initializeTerminal(
    terminalHandle_t toCreate,
    void*            preAllocatedConsoleBuffer,
    uint32_t         preAllocatedConsoleBufferSize,
    void*            preAllocatedRowVector,
    uint16_t         preAllocatedRowVectorSize
);
KTERM_API void destroyTerminal(terminalHandle_t toDestroy);
KTERM_API void terminalWriteString(terminalHandle_t terminal, const char* str, uint32_t length);
KTERM_API void terminalWriteChar(terminalHandle_t terminal, const char c);


#endif /* __KERNEL_TERMINAL_EMULATOR_TERMINAL_STRUCTURE_DEFINITION__ */