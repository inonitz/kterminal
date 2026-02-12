#ifndef __LOGGING_LINKED_LIST_OF_BUFFERS_DEFINITION_HEADER__
#define __LOGGING_LINKED_LIST_OF_BUFFERS_DEFINITION_HEADER__
#include "internal/ringbuffer.h"
#include <internal/atomic_lock.h>


typedef enum {
    LOG_BUF_STATUS_SUCCESS = 0,
    LOG_BUF_STATUS_FULL    = 1,
    LOG_BUF_STATUS_MAX     = 2
} logBufferErr_t;


/*
    Fix sized array containing logs - each node may be/not backed by a char buffer to write to.
*/
typedef struct buffer_of_nodes_pointing_to_finite_sized_char_buffers {
    struct RingBufferNode_t* m_buf;
    uint16_t                 m_bufSize;
    uint16_t                 m_activeLength;
    uint8_t                  m_initialized;
    uint8_t                  m_full;
    casLock_t                m_dataLock; /* Modifying struct members can be atomic, but I can't modify all of them atomically. */
    uint8_t                  m_reserved;
} LogBuffer_t;


void logBufferInitialize(
    LogBuffer_t* toInit,
    char*        initialLogBuffer,
    uint32_t     initialLogBufSize
);


void logBufferDestroy(LogBuffer_t* toDestroy);


logBufferErr_t logBufferSetUnderlyingMemory(
    LogBuffer_t* toModify,
    uint16_t     index,
    char*        buffer,
    uint32_t     size
);


logBufferErr_t logBufferReserve(
    LogBuffer_t* list,
    uint32_t     length,
    char**       locationOfReservedSpace
);


#endif /* __LOGGING_LINKED_LIST_OF_BUFFERS_DEFINITION_HEADER__ */