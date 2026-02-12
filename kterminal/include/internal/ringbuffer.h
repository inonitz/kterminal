#ifndef __KTERM_LOCKLESS_RING_BUFFER_DEFINITION__
#define __KTERM_LOCKLESS_RING_BUFFER_DEFINITION__
#include <internal/types.h>
#include <util2/C/tinycthread.h>


struct RingBufferNode_t {
    char*                    m_bufBegin;
    uint32_t                 m_size;
    uint32_t                 m_currOffset;
    struct RingBufferNode_t* m_next;
    _Atomic(uint8_t)         m_atomicReserveLock;
};


void ringBufferNodeInit(
    struct RingBufferNode_t* toInit,
    char*    buffer,
    uint32_t bufferSize
);


char* ringBufferNodeReserveSpace(
    struct RingBufferNode_t* toInit,
    uint32_t                 length
);


void ringBufferNodeWrite(
    struct RingBufferNode_t* toWrite,
    char*    source,
    uint32_t length
);





#endif /* __KTERM_LOCKLESS_RING_BUFFER_DEFINITION__ */
