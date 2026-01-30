#ifndef __KERNEL_TERMINAL_PRIMITIVE_TYPES_DEFINTION__
#define __KERNEL_TERMINAL_PRIMITIVE_TYPES_DEFINTION__
#include <stdint.h>


#ifndef __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__
typedef uint32_t* framebufferAddress_t;
#endif /* __FRAMEBUFFER_ADDRESS_TYPE_DEFINITION__ */

#ifndef __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__
typedef struct generic_framebuffer_resolution {
    uint16_t width;
    uint16_t height;
} framebufferPixelResolution_t;
#endif /* __FRAMEBUFFER_RESOLUTION_TYPE_DEFINITION__ */


typedef struct terminalInstance* terminalHandle_t;
typedef struct fontStyle_t*      terminalFontStyleHandle_t;


#endif /* __KERNEL_TERMINAL_PRIMITIVE_TYPES_DEFINTION__ */