//
// Created by os on 8/23/23.
//

#include "../h/syscallHandler.hpp"
#include "../lib/hw.h"

#include "../h/Riscv.hpp"
#include "../h/tcb.hpp"
#include "../h/MemoryAllocator.h"
#include "../lib/console.h"
#include "../h/Sem.hpp"

void SysCallHandler::threadDispatch() {
    TCB::timeSliceCounter = 0;//ispocetka broji
    TCB::dispatch();
}

void* SysCallHandler::memAlloc(size_t size) {
    MemoryAllocator* instance = MemoryAllocator::getInstance();
    volatile uint64 sizeInBytes = size*MEM_BLOCK_SIZE;
    return instance->mem_alloc(sizeInBytes);
}

int SysCallHandler::memFree(void* p) {
    MemoryAllocator *instance = MemoryAllocator::getInstance();
    return instance->mem_free(p);
}

int SysCallHandler::threadCreate( thread_t* handle, void(*start_routine)(void*), void* args){
    //volatile uint64* stack =(uint64*) SysCallHandler::memAlloc(sizeof(char)*DEFAULT_STACK_SIZE);
    //alocirati stek
    *handle = TCB::createThread(start_routine, args);//STEK treba proslediti kroz ABI

    if(*handle == 0)
        return -1;
    return 0;
}

int SysCallHandler::threadExit() {
    TCB::running->setFinished(true);
    threadDispatch();

    return 0;
}

void SysCallHandler::threadJoin(thread_t handle) {
    TCB::running->waitingToFinish = handle;
    while(!TCB::running->waitingToFinish->isFinished())
        threadDispatch();

}

char SysCallHandler::getC() {
    return __getc();//iz console.h
}

void SysCallHandler::putC(char c) {
    return __putc(c);
}

int SysCallHandler::semOpen(sem_t *handle, unsigned int init) {
    *handle = Sem::createSemaphore(init);
    return (handle !=0 ? 0 : -1);//returnValue
}

int SysCallHandler::semClose(sem_t handle) {
    return Sem::closeSemaphore(handle);
}

int SysCallHandler::semWait(sem_t id) {
    return id->wait();
}

int SysCallHandler::semSignal(sem_t id) {
    return id->signal();
}

int SysCallHandler::timeSleep(time_t) {//uspavljuje nit na t perioda timer-a
    return 0;
}
