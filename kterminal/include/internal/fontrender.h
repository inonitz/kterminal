#ifndef __KTERM_BASIC_BMFONT_TEXT_RENDERER_DEFINITION__
#define __KTERM_BASIC_BMFONT_TEXT_RENDERER_DEFINITION__
#include <internal/types.h>
#include <kterminal/fonts/fontstyle.h>


typedef position2D_t (*charBlitterTypeGeneric)(
    position2D_t, 
    fontStyle_t   const*, 
    framebuffer_t const*, 
    uint32_t, 
    uint32_t, 
    char
);

typedef position2D_t (*charBlitterTypeU32)(
    position2D_t, 
    fontStyle_t const*, 
    uint32_t    const*, 
    uint32_t, 
    uint32_t, 
    char
);

typedef position2D_t (*charBlitterTypeU24)(
    position2D_t, 
    fontStyle_t   const*, 
    framebuffer_t const*, 
    uint32_t, 
    uint32_t, 
    char
    
);

typedef position2D_t (*charBlitterTypeU16)(
    position2D_t, 
    fontStyle_t const*, 
    uint16_t    const*, 
    uint32_t, 
    uint32_t, 
    char
);



position2D_t renderFixedWidthBMFontChar(
    position2D_t         initialPixelPos,
    fontStyle_t   const* fontToUse,
    framebuffer_t const* renderCanvas,
    uint32_t             foregroundColour, /* Must be in RGB8888 Format */
    uint32_t             backgroundColour, /* Must be in RGB8888 Format */
    char                 character
);


position2D_t renderVariableWidthBMFontChar(
    position2D_t         initialPixelPos,
    fontStyle_t   const* fontToUse,
    framebuffer_t const* renderCanvas,
    uint32_t             foregroundColour, /* Must be in RGB8888 Format */
    uint32_t             backgroundColour, /* Must be in RGB8888 Format */
    char                 character
);


position2D_t renderStringWithBitmapFont(
    position2D_t         initialPosition,
    fontStyle_t   const* fontToUse,
    framebuffer_t const* whereToDraw,
    uint32_t             foregroundColour,
    uint32_t             backgroundColour,
    const char*          stringBegin,
    uint16_t             stringLength
);


#endif /* __KTERM_BASIC_BMFONT_TEXT_RENDERER_DEFINITION__ */