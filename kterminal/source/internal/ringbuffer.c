#include <internal/ringbuffer.h>
#include <stdatomic.h>




void ringBufferNodeInit(
    struct RingBufferNode_t* toInit,
    char*    buffer,
    uint32_t bufferSize
) {
    *toInit = (struct RingBufferNode_t){
        .m_bufBegin       = buffer,
        .m_size           = bufferSize,
        .m_currOffset     = 0,
        .m_next           = NULL,
        .m_atomicReserveLock = 0
    };
    return;
}


char* ringBufferNodeReserveSpace(
    struct RingBufferNode_t* toInit,
    uint32_t                 length
) {

}


void ringBufferNodeWrite(
    struct RingBufferNode_t* toWrite,
    char*    source,
    uint32_t length
) {
    while(!atomic_compare_exchange_strong(&toWrite->m_atomicReserveLock, 0, 1)) {}

    uint64_t       bufOffset   = toWrite->m_currOffset;
    const uint64_t k_bufLength = toWrite->m_size;


    /* likely case: print normally, buffer has enough space */
    if(bufOffset + length < k_bufLength) { 
        for(uint32_t i = 0; i < length; ++i) 
        {
            toWrite->m_bufBegin[bufOffset] = source[i];
            ++bufOffset;
        }
        toWrite->m_currOffset = bufOffset;
        goto goto_block__unlock_and_exit;
    }


    /* Less likely case, we need to circle back to the conOut beginning (we reached the end) */
    uint32_t bytesToWrite = length;
    for(; bufOffset < k_bufLength; ++bufOffset) {
        toWrite->m_bufBegin[bufOffset] = source[length - bytesToWrite];
        --bytesToWrite;
    }
    bufOffset = 0;
    while(bytesToWrite > 0) {
        for(bufOffset = 0; bytesToWrite && bufOffset < k_bufLength; ++bufOffset) {
            toWrite->m_bufBegin[bufOffset] = source[length - bytesToWrite];
            --bytesToWrite;
        }
    }
    toWrite->m_currOffset = bufOffset;


goto_block__unlock_and_exit:
    atomic_store(&toWrite->m_atomicReserveLock, 0);
    return;
}



