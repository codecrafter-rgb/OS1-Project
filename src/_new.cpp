//
// Created by os on 8/17/23.
//

//PREUZETO SA VEZBI

//using size_t = decltype(sizeof(0));//size_t umesto uint64

#include "../h/MemoryAllocator.h"
#include "syscall.h"

#include "../h/syscall_c.h"
#include "../h/syscall_cpp.hpp"

void *operator new(uint64 n) {
    return mem_alloc(n);
}

void *operator new[](uint64 n)
{
    return mem_alloc(n);
}

void operator delete(void *p) {//ne baca izuzetke
    mem_free(p);
}

void operator delete[](void *p) {
    mem_free(p);
}
