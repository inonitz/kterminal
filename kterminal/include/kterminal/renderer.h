#ifndef __KERNEL_TERMINAL_EMULATOR_FONT_RENDERER_DEFINITION__
#define __KERNEL_TERMINAL_EMULATOR_FONT_RENDERER_DEFINITION__
#include <kterminal/kterm_api.h>
#include <kterminal/types.h>


KTERM_API void initializeRenderer(
    bitmapFontRendererHandle_t   toCreate,
    framebufferAddress_t         screenAddress,
    framebufferPixelResolution_t screenSize,
    terminalFontStyleHandle_t    customFontMaybeNull
);


KTERM_API void destroyRenderer(
    bitmapFontRendererHandle_t toDestroy
);


KTERM_API pixelOffset_t fontRendererRenderChar(
    bitmapFontRendererHandle_t renderer,
    uint32_t pixelWidthOffset,
    uint32_t pixelHeightOffset,
    char c
);


KTERM_API pixelOffset_t fontRendererRenderString(
    bitmapFontRendererHandle_t renderer,
    uint32_t pixelWidthOffset,
    uint32_t pixelHeightOffset,
    char c
);


#endif /* __KERNEL_TERMINAL_EMULATOR_FONT_RENDERER_DEFINITION__ */