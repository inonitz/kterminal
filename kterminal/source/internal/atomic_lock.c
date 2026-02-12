#include <internal/atomic_lock.h>
#include <stdatomic.h>


void lock(casLock_t* toLock)
{
    while(!atomic_compare_exchange_strong(toLock, 0, 1)) {}
    return;
}


uint8_t try_lock(casLock_t* toLock)
{
    return atomic_compare_exchange_strong(toLock, 0, 1);
}


void unlock(casLock_t* toLock)
{
    atomic_store(toLock, 0);
    return;
}

