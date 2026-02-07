#include <internal/fontrender.h>
#include <stddef.h>


#define FONT_WIDTH_DYNAMIC 0
#define FONT_WIDTH_STATIC 1


// static void custom_memcpy(
//     void* restrict destination, 
//     void* restrict source, 
//     uint64_t       bytes
// ) {
//     char* chdest = (char*)destination;
//     char* chsrc  = (char*)source;
//     while(bytes) {
//         *chdest = *chsrc;
//         --bytes;
//     }
//     return;
// }



static uint32_t packColourToHardwareFormat(pixelMetadata_t const* pinfo, uint32_t rgba8888) {
    uint8_t r = (rgba8888 >> 0 ) & 0xFF;
    uint8_t g = (rgba8888 >> 8 ) & 0xFF;
    uint8_t b = (rgba8888 >> 16) & 0xFF;

    /* 
        We normalize every Channel to their respective maximum sizes (in bits), 
        and then we put them in their respective bit offsets 
    */
    uint32_t result = 0;
    result |= ( (uint32_t)(r >> (8 - pinfo->m_channelFormats[0].bitWidth)) << pinfo->m_channelFormats[0].bitShift );
    result |= ( (uint32_t)(g >> (8 - pinfo->m_channelFormats[1].bitWidth)) << pinfo->m_channelFormats[1].bitShift );
    result |= ( (uint32_t)(b >> (8 - pinfo->m_channelFormats[2].bitWidth)) << pinfo->m_channelFormats[2].bitShift );
    return result; 
}


/*
    Explanation of the Hierarchy:

    |---Pixel---||---Pixel---| ... |---Pixel---| <--- 8 Pixels == 1 line-Segment
    |---LS---||---LS---| <--- 2/N-Bit line-Segments = 1 Horizontal Glyph Segment
    
    |--HGS--|
    |--HGS--|
    .
    .
    .
    |--HGS--|
        ^ These eventually make up a single glyph. Ofcourse, they're all consecutive in memory.

    All in all:
        * verticalOffset   is an offset to each individual glyph row
        * horizontalOffset is an offset to each glyph-rows' byte
        * bit/i            are offsets to each bit inside byte 

*/
#define TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR(functor_name, pixel_type, is_fixed) \
position2D_t functor_name( \
    position2D_t            pos, \
    fontStyle_t   const*    font, \
    framebuffer_t const*    canvas, \
    genericHardwareColour_t foregroundColour, \
    genericHardwareColour_t backgroundColour, \
    char                    character \
) { \
    union { genericHardwareColour_t in; pixel_type out; } u_fg, u_bg; \
    u_fg.in = foregroundColour; \
    u_bg.in = backgroundColour; \
    pixel_type const hwfg = u_fg.out; \
    pixel_type const hwbg = u_bg.out; \
    \
    \
    uint16_t const  idx                 = (unsigned char)character - font->FirstAsciiCode; \
    uint8_t  const  glyphWidthBits      = (is_fixed) ? font->GlyphBytesWidth * 8 : font->GlyphWidth[idx]; \
    uint8_t  const  glyphWidthFullBytes = glyphWidthBits / 8; \
    uint8_t  const  glyphWidthExtraBits = glyphWidthBits % 8; \
    uint32_t const  fbStride            = canvas->m_pixelsPerScanLine; \
    uint8_t  const* charBitmap     = &font->GlyphBitmaps[(uint64_t)idx * font->GlyphHeight * font->GlyphBytesWidth]; \
    pixel_type*     fbGlyphRowAddr = NULL; \
    pixel_type*     fbRowAddr      = (pixel_type*)( \
        (uint8_t*)canvas->m_baseAddress + sizeof(pixel_type) * (pos.x + fbStride * pos.y) \
    ); \
    \
    \
    uint8_t currentByte = 0; \
    for (uint32_t v = 0; v < font->GlyphHeight; ++v) { \
        fbGlyphRowAddr = fbRowAddr; \
        for (uint32_t h = 0; h < glyphWidthFullBytes; ++h) { \
            currentByte = charBitmap[h]; \
            fbGlyphRowAddr[0] = (currentByte & 0x80) ? hwfg : hwbg; \
            fbGlyphRowAddr[1] = (currentByte & 0x40) ? hwfg : hwbg; \
            fbGlyphRowAddr[2] = (currentByte & 0x20) ? hwfg : hwbg; \
            fbGlyphRowAddr[3] = (currentByte & 0x10) ? hwfg : hwbg; \
            fbGlyphRowAddr[4] = (currentByte & 0x08) ? hwfg : hwbg; \
            fbGlyphRowAddr[5] = (currentByte & 0x04) ? hwfg : hwbg; \
            fbGlyphRowAddr[6] = (currentByte & 0x02) ? hwfg : hwbg; \
            fbGlyphRowAddr[7] = (currentByte & 0x01) ? hwfg : hwbg; \
            fbGlyphRowAddr += 8; \
        } \
        \
        currentByte = charBitmap[glyphWidthFullBytes]; \
        for(uint8_t bit = 0; bit < glyphWidthExtraBits; ++bit) { \
            fbGlyphRowAddr[bit] = (currentByte & (0x80 >> bit)) ? hwfg : hwbg; \
        } \
        fbRowAddr  += fbStride; \
        charBitmap += font->GlyphBytesWidth; \
    } \
    \
    \
    pos.x += glyphWidthBits; \
    return pos; \
} \


TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR(bmfont_blit_uint16_t,         uint16_t, FONT_WIDTH_STATIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR(bmfont_blit_uint32_t,         uint32_t, FONT_WIDTH_STATIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR(bmfont_blit_uint24_t,         rgb24,    FONT_WIDTH_STATIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR(bmfont_blit_dynamic_uint16_t, uint16_t, FONT_WIDTH_DYNAMIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR(bmfont_blit_dynamic_uint32_t, uint32_t, FONT_WIDTH_DYNAMIC)
TEMPLATE_GENERATE_CHAR_BLIT_FUNCTOR(bmfont_blit_dynamic_uint24_t, rgb24,    FONT_WIDTH_DYNAMIC)



// position2D_t renderFixedWidthBMFontChar(
//     position2D_t         initialPixelPos,
//     fontStyle_t   const* fontToUse,
//     framebuffer_t const* renderCanvas,
//     uint32_t             foregroundColour,
//     uint32_t             backgroundColour,
//     char                 character
// ) {
//     fontToUse = (fontToUse == NULL) ? &FontStyle_Consolas12 : fontToUse;
//     uint32_t             tmp                = 0;
//     uint32_t             currentPixelColour = 0;
//     uint32_t             pixelOffset        = 0;
// 	framebufferAddress_t pixelAddress       = NULL;
//     uint8_t const*       bitmapBuffer       = NULL;
//     uint8_t              indexInBitmap      = character - fontToUse->FirstAsciiCode; /* First ASCII tells us where's the start of the bitmap */
//     const uint8_t        pixelSizeBytes     = renderCanvas->m_pixelInfo.m_sizeBytes;


//     pixelAddress = ((uint8_t*)renderCanvas->m_baseAddress) + pixelSizeBytes * (initialPixelPos.x + renderCanvas->m_pixelsPerScanLine * initialPixelPos.y);
//     tmp  = indexInBitmap;
//     tmp *= fontToUse->GlyphHeight * fontToUse->GlyphBytesWidth; /* sizeof(GlyphBitmaps[0])  */
//     bitmapBuffer = &fontToUse->GlyphBitmaps[tmp];


//     foregroundColour = packColourToHardwareFormat(&renderCanvas->m_pixelInfo, foregroundColour);
//     backgroundColour = packColourToHardwareFormat(&renderCanvas->m_pixelInfo, backgroundColour);



//     uint8_t bitIsEnabled = 1;
//     for(uint32_t v = 0; v < fontToUse->GlyphHeight; ++v) {
//         for(uint32_t h = 0; h < fontToUse->GlyphBytesWidth; ++h) {
            
//             pixelOffset = h * (8 * pixelSizeBytes);
//             for(uint8_t bit = 0; bit < 8; ++bit) {
//                 bitIsEnabled = (*bitmapBuffer) & (0x80 >> bit);
//                 currentPixelColour = bitIsEnabled ? foregroundColour : backgroundColour;
                
//                 for(uint8_t pixelByte = 0; pixelByte < pixelSizeBytes; ++pixelByte) {
//                     pixelAddress[pixelOffset + bit * pixelSizeBytes + pixelByte] = (currentPixelColour >> (8 * pixelByte)) & 0xFF;
//                 }
//             }
//             ++bitmapBuffer;
//         }

//         /* Move to next line to render. */
//         pixelAddress += (ptrdiff_t)renderCanvas->m_pixelsPerScanLine * pixelSizeBytes;
//     }
    
//     initialPixelPos.x += fontToUse->GlyphBytesWidth * 8;

//     return initialPixelPos;
// }





// position2D_t renderVariableWidthBMFontChar(
//     position2D_t         initialPixelPos,
//     fontStyle_t   const* fontToUse,
//     framebuffer_t const* renderCanvas,
//     uint32_t             foregroundColour,
//     uint32_t             backgroundColour,
//     char                 character
// ) {
//     fontToUse = (fontToUse == NULL) ? &FontStyle_Consolas12 : fontToUse;
//     uint32_t             tmp                = 0;
//     uint32_t             currentPixelColour = 0;
//     uint32_t             pixelOffset        = 0;
// 	framebufferAddress_t pixelAddress       = NULL;
//     uint8_t const*       bitmapBuffer       = NULL;
//     uint8_t              indexInBitmap      = character - fontToUse->FirstAsciiCode; /* First ASCII tells us where's the start of the bitmap */
//     const uint8_t        pixelSizeBytes     = renderCanvas->m_pixelInfo.m_sizeBytes;


//     pixelAddress = ((uint8_t*)renderCanvas->m_baseAddress) + pixelSizeBytes * (initialPixelPos.x + renderCanvas->m_pixelsPerScanLine * initialPixelPos.y);
//     tmp  = indexInBitmap;
//     tmp *= fontToUse->GlyphHeight * fontToUse->GlyphBytesWidth; /* sizeof(GlyphBitmaps[0])  */
//     bitmapBuffer = &fontToUse->GlyphBitmaps[tmp];


//     foregroundColour = packColourToHardwareFormat(&renderCanvas->m_pixelInfo, foregroundColour);
//     backgroundColour = packColourToHardwareFormat(&renderCanvas->m_pixelInfo, backgroundColour);


//     /*
//         |---Pixel---||---Pixel---| ... |---Pixel---| <--- 8 Pixels == 1 line-Segment
//         |---LS---||---LS---| <--- 2/N-Bit line-Segments = 1 Horizontal Glyph Segment
        
//         |--HGS--|
//         |--HGS--|
//         .
//         .
//         .
//         |--HGS--|
//             ^ These eventually make up a single glyph. Ofcourse, they're all consecutive in memory.

//         All in all:
//             * verticalOffset   is an offset to each individual glyph row
//             * horizontalOffset is an offset to each glyph-rows' byte
//             * bit/i            are offsets to each bit inside byte 

//     */
//     uint8_t bitIsEnabled = 1;
//     uint8_t tmpBitWidth  = fontToUse->GlyphWidth[indexInBitmap];
//     for(uint32_t verticalOffset = 0; verticalOffset < fontToUse->GlyphHeight; ++verticalOffset) {
//         // for(uint32_t horizontalOffset = 0; horizontalOffset < fontToUse->GlyphBytesWidth; ++horizontalOffset) {
//         for(uint8_t bit = 0; bit < tmpBitWidth; ++bit) {
            
//                 bitIsEnabled = (*bitmapBuffer) & ( (1 << tmpBitWidth) >> bit);
//                 currentPixelColour = bitIsEnabled ? foregroundColour : backgroundColour;
                
//                 for(uint8_t pixelByte = 0; pixelByte < pixelSizeBytes; ++pixelByte) {
//                     pixelAddress[pixelOffset + bit * pixelSizeBytes + pixelByte] = (currentPixelColour >> (8 * pixelByte)) & 0xFF;
//                 }
//         }
//             ++bitmapBuffer;
//         // }

//         /* Move to next line to render. */
//         pixelAddress += (ptrdiff_t)renderCanvas->m_pixelsPerScanLine * pixelSizeBytes;
//     }
    
//     initialPixelPos.x += fontToUse->GlyphBytesWidth * 8;

//     return initialPixelPos;
// }


// position2D_t renderStringWithBitmapFont(
//     position2D_t         initialPosition,
//     fontStyle_t   const* fontToUse,
//     framebuffer_t const* whereToDraw,
//     uint32_t             foregroundColour,
//     uint32_t             backgroundColour,
//     const char*          stringBegin,
//     uint16_t             stringLength
// ) {
//     genericHardwareColour_t foreground;
//     genericHardwareColour_t background;

//     foreground.u32 = foregroundColour;
//     background.u32 = backgroundColour;
//     foreground.u32 = packColourToHardwareFormat(&whereToDraw->m_pixelInfo, foreground.u32);
//     background.u32 = packColourToHardwareFormat(&whereToDraw->m_pixelInfo, background.u32);
//     for(uint16_t i = 0; i < stringLength; ++i) {
//         initialPosition = whereToDraw->m_drawChar(
//             initialPosition, 
//             fontToUse, 
//             whereToDraw, 
//             foreground, 
//             background,
//             stringBegin[i]
//         );
//     }
// }

