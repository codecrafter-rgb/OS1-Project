//
// Created by os on 8/16/23.
//

//PREUZETO SA VEZBI

#include "../h/tcb.hpp"
#include "../h/Riscv.hpp"


#include "../h/syscall_c.h"
#include "../h/syscallHandler.hpp"

TCB* TCB::running = nullptr; //default vrednost

uint64 TCB::timeSliceCounter = 0;//koliko je proslo perioda duzine timeSlice

TCB *TCB::createThread(Body body, void* args) {
    return new TCB(body, TIME_SLICE, args);//treba DEFAULT_TIME_SLICE
}

void* TCB::operator new(size_t size) {
    return (void*) SysCallHandler::memAlloc((size+MEM_BLOCK_SIZE-1)/MEM_BLOCK_SIZE);
}

void TCB::operator delete(void* p) {
    SysCallHandler::memFree(p);
}

//menja tekuci thread i kontekst
void TCB::dispatch() {
    TCB *old = running;
    if(!old->isFinished()) {
        Scheduler::put(old);
    }

    running = Scheduler::get();

    TCB::contextSwitch(&old->context, &running->context);
}

void TCB::threadWrapper() {
    Riscv::popSppSpie();                //vrsi povratak iz prekidne rutine //breakpoint
    running->body(running->arguments);                  //breakpoint
    running->setFinished(true);             //tek kada se zavrsi body, oznacava se kao gotova nit
    thread_dispatch(); 
}
