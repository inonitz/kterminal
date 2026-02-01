#ifndef __KERNEL_TERMINAL_EMULATOR_INTERNAL_TYPES_DEFINITION__
#define __KERNEL_TERMINAL_EMULATOR_INTERNAL_TYPES_DEFINITION__
#include <stdint.h>


#ifndef __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__
#   define __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__
#endif /* __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__ */
#ifndef __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
#   define __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
#endif /* __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__ */
#ifndef __GENERIC_CHARBUF_TYPE_DEFINITION__
#   define __GENERIC_CHARBUF_TYPE_DEFINITION__
#endif /* __GENERIC_CHARBUF_TYPE_DEFINITION__ */
#ifndef __ROWVECTOR_CHARMARKER_TYPE_DEFINITION__
#   define __ROWVECTOR_CHARMARKER_TYPE_DEFINITION__
#endif /* __ROWVECTOR_CHARMARKER_TYPE_DEFINITION__ */
#ifndef __TERMINAL_INSTANCE_TYPE_DEFINITION__
#   define __TERMINAL_INSTANCE_TYPE_DEFINITION__
#endif /* __TERMINAL_INSTANCE_TYPE_DEFINITION__ */
#ifndef __TERMINAL_FONT_STYLE_TYPE_DEFINITION__
#   define __TERMINAL_FONT_STYLE_TYPE_DEFINITION__
#endif /* __TERMINAL_FONT_STYLE_TYPE_DEFINITION__ */
#ifndef __FRAMEBUFFER_BACKED_TEXT_RENDERER_TYPE_DEFINITION__
#   define __FRAMEBUFFER_BACKED_TEXT_RENDERER_TYPE_DEFINITION__
#endif /* __FRAMEBUFFER_BACKED_TEXT_RENDERER_TYPE_DEFINITION__ */
#ifndef __TERMINAL_COMPOSITION_TYPE_DEFINITION__
#   define __TERMINAL_COMPOSITION_TYPE_DEFINITION__
#endif /* __TERMINAL_COMPOSITION_TYPE_DEFINITION__ */


#ifdef __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__
typedef uint32_t* framebufferAddress_t;
#endif /* __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__ */


#ifdef __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
typedef struct generic_vector_2_shorts_type {
    uint16_t m_width;
    uint16_t m_height;
} pixelOffset_t;
typedef pixelOffset_t framebufferPixelResolution_t;
#endif /* __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__ */


#ifdef __GENERIC_CHARBUF_TYPE_DEFINITION__
typedef struct generic_characterbuffer_stringlike {
    char*    m_buf;
    uint32_t m_length;
    uint32_t m_currentOffset;
} charbuf_t;
#endif /* __GENERIC_CHARBUF_TYPE_DEFINITION__ */


#ifdef __ROWVECTOR_CHARMARKER_TYPE_DEFINITION__

typedef struct terminal_row_pointer_type {
    uint32_t m_index;
    uint32_t m_length;
} terminalRow_t;
#endif /* __ROWVECTOR_CHARMARKER_TYPE_DEFINITION__ */


#ifdef __TERMINAL_INSTANCE_TYPE_DEFINITION__
/* The whole thing is essentially a circular buffer for a maximal amount of lines. */
// typedef struct terminal_structure_definition {
//     // charbuf_t  m_conIn;          /* Dynamic Arrays that contain all Input         History */
//     // charbuf_t  m_conOut;         /* Dynamic Arrays that contain all Output        History */
//     // charbuf_t  m_conErr;         /* Dynamic Arrays that contain all Error/Warning History */
//     charbuf_t                    m_consoleOut;     /* Fixed Buffer to store as much terminal history. */
//     charbuf_t                    m_consoleHistory; /* Dynamic Buffer to store all terminal history (if possible). */
//     framebufferAddress_t         m_pixelAddress;   
//     framebufferPixelResolution_t m_framebufferSize;
//     uint16_t                     m_currentTopRow;
//     uint8_t                      m_reserved[2];
//     // const uint16_t               m_maxColumns;     /* screenHeight / glyphHeight */
//     // const uint16_t               m_maxCharsPerRow; /* ScreenWidth / glyphWidth   */
// } terminal_t;


typedef struct terminal_structure_definition__version3 {
    charbuf_t      m_consoleOut;
    terminalRow_t* m_rowVector;
    uint32_t       m_rowVectorSize;
    int32_t        m_currentTop;
} terminal_t;


typedef terminal_t* terminalHandle_t;
#endif /* __TERMINAL_INSTANCE_TYPE_DEFINITION__ */


#ifdef __TERMINAL_FONT_STYLE_TYPE_DEFINITION__
#include <kterminal/fonts/Consolas12_bmp.h>
typedef fontStyle_t terminalFontStyle_t;
typedef terminalFontStyle_t* terminalFontStyleHandle_t;
#endif /* __TERMINAL_FONT_STYLE_TYPE_DEFINITION__ */


#ifdef __FRAMEBUFFER_BACKED_TEXT_RENDERER_TYPE_DEFINITION__
typedef struct primitive_bitmap_font_renderer_type {
    terminalFontStyleHandle_t    m_textStyle;
    framebufferAddress_t         m_framebuffer;
    framebufferPixelResolution_t m_framebufSize;
    // const uint16_t            m_rowsPerChar;
    // const uint16_t            m_colsPerChar;
    // const uint16_t            m_rowsPixelRemainder;
    // const uint16_t            m_colsPixelRemainder;
} bitmapFontRenderer_t;

typedef bitmapFontRenderer_t* bitmapFontRendererHandle_t;
#endif /* __FRAMEBUFFER_BACKED_TEXT_RENDERER_TYPE_DEFINITION__ */


#ifdef __TERMINAL_COMPOSITION_TYPE_DEFINITION__
typedef struct terminal_emulator_struct_type_definition {
    uint16_t             m_horizonalOffset;
    uint16_t             m_verticalOffset;
    uint8_t              m_reserved[4];
    terminal_t           m_text;
    bitmapFontRenderer_t m_renderer;
    // const uint16_t    m_textOffset;
    // const uint16_t    m_spaceOffset;
} terminal_emulator_t;

#endif /* __TERMINAL_COMPOSITION_TYPE_DEFINITION__ */


#endif /* __KERNEL_TERMINAL_EMULATOR_INTERNAL_TYPES_DEFINITION__ */