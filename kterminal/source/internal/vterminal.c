#include <stddef.h>
#include <internal/vterminal.h>


const uint16_t pixelHorizontalSpaceBetweenCharacters = 2;
const uint16_t pixelVerticalSpaceBetweenCharacters   = 2;



void initializeTerminalEmulator(
    terminalEmulator_t*  toCreate,
    rowSpan_t*           preAllocatedSpanBufferDependingOnFramebufferResolution,
    LoggingRingBuffer_t* preAllocatedLoggingBuffer,
    framebuffer_t*       framebufferDescription
) {
    *toCreate = (terminalEmulator_t){
        (position2D_t){0, 0},
        preAllocatedSpanBufferDependingOnFramebufferResolution,
        *preAllocatedLoggingBuffer,
        framebufferDescription
    };
    return;
}


void destroyTerminalEmulator(
    terminalEmulator_t* toDestroy
) {
    toDestroy->m_cursor = (position2D_t){0, 0};
    toDestroy->m_drawBuffer = (framebuffer_t){ NULL, (position2D_t){0, 0} };
    return;
}