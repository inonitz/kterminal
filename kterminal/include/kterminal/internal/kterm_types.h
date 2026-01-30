#ifndef __KERNEL_TERMINAL_EMULATOR_INTERNAL_TYPES_DEFINITION__
#define __KERNEL_TERMINAL_EMULATOR_INTERNAL_TYPES_DEFINITION__
#include <stdint.h>


#ifndef __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__
#   define __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__
#endif
#ifndef __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
#   define __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
#endif
#ifndef __GENERIC_CHARBUF_TYPE_DEFINITION__
#   define __GENERIC_CHARBUF_TYPE_DEFINITION__
#endif
#ifndef __TERMINAL_INSTANCE_TYPE_DEFINITION__
#   define __TERMINAL_INSTANCE_TYPE_DEFINITION__
#endif
#ifndef __TERMINAL_FONT_STYLE_TYPE_DEFINITION__
#   define __TERMINAL_FONT_STYLE_TYPE_DEFINITION__
#endif


#ifdef __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__
typedef uint32_t* framebufferAddress_t;
#endif /* __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__ */


#ifdef __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
typedef struct generic_framebuffer_resolution {
    uint16_t m_width;
    uint16_t m_height;
} framebufferPixelResolution_t;
#endif /* __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__ */


#ifdef __GENERIC_CHARBUF_TYPE_DEFINITION__
typedef struct generic_characterbuffer_stringlike {
    char*    m_buf;
    uint16_t m_length;
} charbuf_t;
#endif /* __GENERIC_CHARBUF_TYPE_DEFINITION__ */


#ifdef __TERMINAL_INSTANCE_TYPE_DEFINITION__
/* The whole thing is essentially a circular buffer for a maximal amount of lines. */
typedef struct terminal_structure_definition {
    charbuf_t  m_history;        /* a multiple of totalSize (in the next entry): contains the history of all written characters in the terminal, upto a limit */
    charbuf_t* m_rows;           /* dynamic array of rows, will be backed by a huge charbuf_t region that's allocated in boot services: totalSize = width * height / (fontPixelWidth * fontPixelHeight) */
    uint16_t   m_maxCharsPerRow; /* ScreenWidth / glyphWidth   */
    uint16_t   m_maxColumns;     /* screenHeight / glyphHeight */
    uint16_t   m_currentTopRow;

} terminal_t;
typedef terminal_t* terminalHandle_t;
#endif /* __TERMINAL_INSTANCE_TYPE_DEFINITION__ */


#ifdef __TERMINAL_FONT_STYLE_TYPE_DEFINITION__
#include <kterminal/fonts/Consolas12_bmp.h>
typedef fontStyle_t terminalFontStyle_t;
typedef terminalFontStyle_t* terminalFontStyleHandle_t;
#endif /* __TERMINAL_FONT_STYLE_TYPE_DEFINITION__ */








#endif /* __KERNEL_TERMINAL_EMULATOR_INTERNAL_TYPES_DEFINITION__ */