#ifndef __KERNEL_TERMINAL_EMULATOR_DEFINITION__
#define __KERNEL_TERMINAL_EMULATOR_DEFINITION__
#include <kterminal/kterm_api.h>
#include <kterminal/types.h>




KTERM_API void initializeTerminal(
    terminalHandle_t             toCreate,
    framebufferAddress_t         screenAddress,
    framebufferPixelResolution_t screenSize,
    terminalFontStyle_t          customFontMaybeNull
);
KTERM_API void destroyTerminal(terminalHandle_t toDestroy);
KTERM_API void writeString(terminalHandle_t terminal, const char* str, uint32_t length);
KTERM_API void writeChar(terminalHandle_t terminal, const char c);
// void redraw(terminalHandle_t terminal);



#endif /* __KERNEL_TERMINAL_EMULATOR_DEFINITION__ */