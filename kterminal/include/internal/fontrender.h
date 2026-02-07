#ifndef __KTERM_BASIC_BMFONT_TEXT_RENDERER_DEFINITION__
#define __KTERM_BASIC_BMFONT_TEXT_RENDERER_DEFINITION__
#include <internal/types.h>
#include <kterminal/fonts/fontstyle.h>


#ifndef TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR_DEFINITION
#   define TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR_DEFINITION(functor_name, pixel_type, is_fixed) \
position2D_t functor_name( \
    position2D_t            pos, \
    fontStyle_t   const*    font, \
    framebuffer_t const*    canvas, \
    genericHardwareColour_t foregroundColour, \
    genericHardwareColour_t backgroundColour, \
    char                    character \
); \

#endif /* TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR_DEFINITION */


TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR_DEFINITION(bmfont_blit_uint16_t,         uint16_t, FONT_WIDTH_STATIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR_DEFINITION(bmfont_blit_uint32_t,         uint32_t, FONT_WIDTH_STATIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR_DEFINITION(bmfont_blit_uint24_t,         rgb24,    FONT_WIDTH_STATIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR_DEFINITION(bmfont_blit_dynamic_uint16_t, uint16_t, FONT_WIDTH_DYNAMIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR_DEFINITION(bmfont_blit_dynamic_uint32_t, uint32_t, FONT_WIDTH_DYNAMIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR_DEFINITION(bmfont_blit_dynamic_uint24_t, rgb24,    FONT_WIDTH_DYNAMIC)


// position2D_t renderStringWithBitmapFont(
//     position2D_t         initialPosition,
//     fontStyle_t   const* fontToUse,
//     framebuffer_t const* whereToDraw,
//     uint32_t             foregroundColour,
//     uint32_t             backgroundColour,
//     const char*          stringBegin,
//     uint16_t             stringLength
// );

#endif /* __KTERM_BASIC_BMFONT_TEXT_RENDERER_DEFINITION__ */