#include <internal/logbuffer.h>
#include <internal/ringbuffer.h>
#include <string.h>


void logBufferInitialize(
    LogBuffer_t* toInit,
    char*        initialLogBuffer,
    uint32_t     initialLogBufSize
) {
    static const uint16_t m_localNodeAmount = 512;
    static struct RingBufferNode_t m_localNodes[m_localNodeAmount];

    if(toInit->m_initialized) {
        return;
    }


    lock(&toInit->m_dataLock);
    for(uint8_t i = 0; i < m_localNodeAmount; ++i) {
        m_localNodes[i] = (struct RingBufferNode_t){
            NULL, 0, 0, NULL, 0
        };
    }

    *toInit = (LogBuffer_t){
        .m_buf          = &m_localNodes[0],
        .m_bufSize      = m_localNodeAmount,
        .m_activeLength = 0,
        .m_initialized  = 1,
        .m_full         = 0,
        .m_reserved     = 0
    };
    toInit->m_buf[toInit->m_activeLength] = (struct RingBufferNode_t){
        .m_bufBegin       = initialLogBuffer,
        .m_size           = initialLogBufSize,
        .m_currOffset     = 0,
        .m_next           = NULL,
        .m_atomicReserveLock = 0
    };
    unlock(&toInit->m_dataLock);
    
    
    return;
}


void logBufferDestroy(LogBuffer_t* toDestroy)
{
    if(toDestroy == NULL) {
        return;
    }


    lock(&toDestroy->m_dataLock);

    if(toDestroy->m_buf != NULL) {
        memset(toDestroy->m_buf, 0x00, toDestroy->m_bufSize * sizeof(struct RingBufferNode_t));
    }
    memset(toDestroy, 0x00, sizeof(LogBuffer_t));

    unlock(&toDestroy->m_dataLock);
    return;
}


/*
    If a process called this function, gets interrupted,
    and the interrupt handler also uses this lock (or the handler itself),
    this'll eventually become a deadlock.
    Need to fix the lock & unlock functions.
*/
logBufferErr_t logBufferSetUnderlyingMemory(
    LogBuffer_t* toModify,
    uint16_t     index,
    char*        buffer,
    uint32_t     size
) {
    lock(&toModify->m_dataLock);
    toModify->m_buf[index].m_bufBegin = buffer;
    toModify->m_buf[index].m_size     = size;
    unlock(&toModify->m_dataLock);
    return LOG_BUF_STATUS_SUCCESS;
}


logBufferErr_t logBufferReserve(
    LogBuffer_t* list,
    uint32_t       length,
    char**         locationOfReservedSpace
) {
    struct RingBufferNode_t* tmp = list->m_activeHead;
    
    lock(&list->m_dataLock);
    uint32_t available = tmp->m_size - tmp->m_currOffset;


    if(list->m_activeHead == list->m_tail && list->m_full) {
        return LOG_LIST_STATUS_FULL;
    }


    if(available < length) {
        list->m_activeHead = list->m_activeHead->m_next;
        ++list->m_activeLength;
        
        available = tmp->m_size - tmp->m_currOffset;
    }
    return tmp->m_bufBegin + (tmp->m_size - 1 - tmp->m_remainingSpace)
}