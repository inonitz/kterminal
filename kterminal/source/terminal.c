#include <kterminal/internal/kterm_types.h>


static uint32_t probeForNewline(
    charbuf_t buf,
    uint32_t beginOffset,
    uint32_t endOffset
);


void initializeTerminal(
    terminalHandle_t toCreate,
    void*            preAllocatedConsoleBuffer,
    uint32_t         preAllocatedConsoleBufferSize,
    void*            preAllocatedRowVector,
    uint16_t         preAllocatedRowVectorSize
) {
    toCreate->m_consoleOut = (charbuf_t){
        preAllocatedConsoleBuffer,
        preAllocatedConsoleBufferSize,
        0
    };
    toCreate->m_rowVector  = (terminalRow_t*)preAllocatedRowVector;
    toCreate->m_rowVectorSize = 0;
    toCreate->m_currentTop    = -1;
    return;
}


void destroyTerminal(terminalHandle_t toDestroy)
{
    for(uint32_t i = 0; i < toDestroy->m_consoleOut.m_length; ++i) {
        toDestroy->m_consoleOut.m_buf[i] = 0;
    }
    for(uint32_t i = 0; i < toDestroy->m_rowVectorSize; ++i) {
        toDestroy->m_rowVector[i] = (terminalRow_t){0, 0};
    }
    toDestroy->m_rowVectorSize = 0;
    toDestroy->m_currentTop    = -1;
    return;
}


void terminalWriteString(terminalHandle_t terminal, const char* str, uint32_t length)
{
    uint64_t       conOffset       = terminal->m_consoleOut.m_currentOffset;
    const uint64_t k_termBufLength = terminal->m_consoleOut.m_length;

    /* likely case: print normally, buffer has enough space */
    if(conOffset + length < k_termBufLength) { 
        for(uint32_t i = 0; i < length; ++i) 
        {
            terminal->m_consoleOut.m_buf[conOffset] = str[i];
            ++conOffset;
        }
        terminal->m_consoleOut.m_currentOffset = conOffset;
        return;
    }


    /* Less likely case, we need to circle back to the conOut beginning (we reached the end) */
    uint32_t bytesToWrite = length;
    for(; conOffset < k_termBufLength; ++conOffset) {
        terminal->m_consoleOut.m_buf[conOffset] = str[length - bytesToWrite];
        --bytesToWrite;
    }
    conOffset = 0;
    while(bytesToWrite > 0) {
        for(conOffset = 0; bytesToWrite && conOffset < k_termBufLength; ++conOffset) {
            terminal->m_consoleOut.m_buf[conOffset] = str[length - bytesToWrite];
            --bytesToWrite;
        }
    }

    terminal->m_consoleOut.m_currentOffset = conOffset;


    charbuf_t probeString = {
        str,
        length,
        0
    };
    probeString.m_currentOffset = probeForNewline(probeString, 0, length);
    if(probeString.m_currentOffset != length) {
        if(terminal->m_currentTop == -1) {
            
        }
    }

    return;
}


void terminalWriteChar(terminalHandle_t terminal, const char c)
{
    uint32_t* offset = &terminal->m_consoleOut.m_currentOffset;

    *offset = (*offset == terminal->m_consoleOut.m_length) ? 0 : *offset;
    terminal->m_consoleOut.m_buf[*offset] = c;
    return;
}




static uint32_t probeForNewline(
    charbuf_t buf,
    uint32_t  beginOffset,
    uint32_t  endOffset
) {
    /* it is assumed that endOffset < buf->length && beginOffset <= endOffset */
    endOffset -= beginOffset;
    beginOffset = 0;

    for(; buf.m_buf[beginOffset] != '\n' && beginOffset < endOffset; ++beginOffset);
    
    return beginOffset; /* if the returned value == original(endOffset) then we didn't find any */
}