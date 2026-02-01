#include <kterminal/renderer.h>
#include <kterminal/internal/kterm_types.h>
#include <kterminal/fonts/Consolas12_bmp.h>



void initializeRenderer(
    bitmapFontRendererHandle_t   toCreate,
    framebufferAddress_t         screenAddress,
    framebufferPixelResolution_t screenSize,
    terminalFontStyleHandle_t    customFontMaybeNull
) {
    toCreate->m_textStyle    = (customFontMaybeNull == NULL) ? &FontStyle_Consolas12 : customFontMaybeNull;
    toCreate->m_framebuffer  = screenAddress;
    toCreate->m_framebufSize = screenSize;
    return;
}


void destroyRenderer(
    bitmapFontRendererHandle_t toDestroy
) {
    toDestroy->m_textStyle = NULL;
    toDestroy->m_framebuffer = NULL;
    toDestroy->m_framebufSize = (framebufferPixelResolution_t){0, 0};
    return;
}


pixelOffset_t fontRendererRenderChar(
    bitmapFontRendererHandle_t renderer,
    uint32_t pixelWidthOffset,
    uint32_t pixelHeightOffset,
    char c
);


pixelOffset_t fontRendererRenderString(
    bitmapFontRendererHandle_t renderer,
    uint32_t pixelWidthOffset,
    uint32_t pixelHeightOffset,
    char c
);