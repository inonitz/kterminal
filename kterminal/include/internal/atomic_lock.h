#ifndef __ATOMIC_COMPARE_AND_SWAP_LOCK_DEFINITION__
#define __ATOMIC_COMPARE_AND_SWAP_LOCK_DEFINITION__
#include <stdint.h>


typedef _Atomic(uint8_t) casLock_t;


void    lock(casLock_t* toLock);
uint8_t try_lock(casLock_t* toLock);
void    unlock(casLock_t* toLock);


#endif /* __ATOMIC_COMPARE_AND_SWAP_LOCK_DEFINITION__ */