#ifndef __KERNEL_TERMINAL_EMULATOR_COMMON_TYPES_DEFINITION__
#define __KERNEL_TERMINAL_EMULATOR_COMMON_TYPES_DEFINITION__
#include <stdint.h>


typedef struct generic_position_16bit_type_definition {
    uint16_t x;
    uint16_t y;
} position2D_t;


typedef uint8_t* framebufferAddress_t;


typedef struct __uefi_individual_pixel_channel_format_type {
	uint8_t bitWidth;
	uint8_t bitShift;
} pixelChannelFormat_t;


typedef struct __uefi_framebuffer_pixel_format_type {
	uint8_t  			 m_sizeBytes;
	uint8_t  			 m_enumFormat;
	pixelChannelFormat_t m_channelFormats[3];
} pixelMetadata_t;


typedef struct generic_framebuffer_type_definition {
	void*           	   m_baseAddress;
    position2D_t    	   m_size;
	uint16_t        	   m_pixelsPerScanLine;
	pixelMetadata_t 	   m_pixelInfo;
	charBlitterTypeGeneric
} framebuffer_t;


#endif /* __KERNEL_TERMINAL_EMULATOR_COMMON_TYPES_DEFINITION__ */