#ifndef __KERNEL_TERMINAL_PRIMITIVE_TYPES_DEFINTION__
#define __KERNEL_TERMINAL_PRIMITIVE_TYPES_DEFINTION__
#include <stdint.h>


#ifndef __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__
typedef uint32_t* framebufferAddress_t;
#endif /* __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__ */

#ifndef __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
#   define __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
#endif /* __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__ */


#ifdef __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
typedef struct generic_vector_2_shorts_type {
    uint16_t m_width;
    uint16_t m_height;
} pixelOffset_t;
typedef pixelOffset_t framebufferPixelResolution_t;
#endif /* __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__ */

typedef struct terminalInstance*     terminalHandle_t;
typedef struct fontStyle_t*          terminalFontStyleHandle_t;
typedef struct bitmapFontRenderer_t* bitmapFontRendererHandle_t;

#endif /* __KERNEL_TERMINAL_PRIMITIVE_TYPES_DEFINTION__ */