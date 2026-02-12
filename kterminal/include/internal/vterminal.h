#ifndef __KTERM_UNIDIRECTIONAL_TERMINAL_EMULATOR_DEFINITION__
#define __KTERM_UNIDIRECTIONAL_TERMINAL_EMULATOR_DEFINITION__
#include <internal/ringbuffer.h>
#include <internal/fontrender.h>


typedef struct terminal_row_span_type_definition {
    uint32_t m_beginIndex;
    uint32_t m_endIndex;
} rowSpan_t;


/*
    The Terminal Can currently only output data frsom a char-stream
    In the future (When relevant), I'll modify this to add bidirectional data movement for an eventual shell emulator
*/
typedef struct output_only_terminal_emulator_type_definition {
    position2D_t        m_cursor;
    rowSpan_t*          m_rowBuf; /* array of spans, each of which index into m_log in respective offsets */


    LoggingRingBuffer_t m_log;
    framebuffer_t       m_drawBuffer;
} terminalEmulator_t;


void initializeTerminalEmulator(
    terminalEmulator_t*  toCreate,
    rowSpan_t*           preAllocatedSpanBufferDependingOnFramebufferResolution,
    LoggingRingBuffer_t* preAllocatedLoggingBuffer,
    framebuffer_t*       framebufferDescription
);


void destroyTerminalEmulator(
    terminalEmulator_t* toDestroy
);


#endif /* __KTERM_UNIDIRECTIONAL_TERMINAL_EMULATOR_DEFINITION__ */