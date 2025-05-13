//
// Created by os on 8/22/23.
//

#include "../lib/hw.h"
#include "../h/MemoryAllocator.h"
#include "../h/tcb.hpp"

#include "../h/syscall_c.h"
#include "../h/syscallHandler.hpp"//delete


void thread_dispatch() {
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::threadDispatch));
    __asm__ volatile ("ecall");
    //nema return value
}

void *mem_alloc(size_t size) {
    //racuna broj blokova za zadati mem_alloc
    size = (size + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;// [size/MEM_BLOCK_SIZE]
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(size));//ubaca se obrnutim redosledom, iz nizih registara u vise

    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::memAlloc));//breakpoint
    __asm__ volatile ("ecall");//breakpoint

    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (void *) returnValue;
}


int mem_free(void *p) {
    //OBRNUTIM Redosledom u registre
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(p));
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::memFree));
    __asm__ volatile ("ecall");

    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (int) returnValue;
}


int thread_create(thread_t *handle, void (*start_routine)(void *), void *arg) {
    //NIT SAMO STAVLJA U RED SPREMNIH, NE POKRECE JE ODMAH
    //volatile uint64* stack =(uint64*) SysCallHandler::memAlloc(DEFAULT_STACK_SIZE);
    //if(stack==0) return -1;//greska u alociranju steka
    //__asm__ volatile("mv a4, %[a4]" : : [a4] "r"(stack));
    __asm__ volatile("mv a3, %[a3]" : : [a3] "r"(arg));
    __asm__ volatile("mv a2, %[a2]" : : [a2] "r"(start_routine));
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(handle));
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::threadCreate));
    __asm__ volatile ("ecall");
    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (int) returnValue;
}

int thread_exit() {
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::threadExit));
    __asm__ volatile ("ecall");
    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (int) returnValue;
}

void thread_join(thread_t handle) {
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(handle));
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::threadJoin));
    __asm__ volatile ("ecall");
}

int sem_open(sem_t *handle, unsigned int init) {
    __asm__ volatile("mv a2, %[a2]" : : [a2] "r"(init));
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(handle));
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::semOpen));
    __asm__ volatile ("ecall");
    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (int) returnValue;
}

int sem_close(sem_t handle) {
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(handle));
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::semClose));
    __asm__ volatile ("ecall");
    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (int) returnValue;
}

int sem_wait(sem_t id) {
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(id));
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::semWait));
    __asm__ volatile ("ecall");
    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (int) returnValue;
}

int sem_signal(sem_t id) {
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(id));
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::semSignal));
    __asm__ volatile ("ecall");
    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (int) returnValue;
}

int time_sleep(time_t time) {
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(time));
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::timeSleep));
    __asm__ volatile ("ecall");
    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (int) returnValue;
}

char getc() {
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::getC));
    __asm__ volatile ("ecall");
    volatile uint64 returnValue;
    __asm__ volatile("mv %[a0], a0" : [a0] "=r"(returnValue));
    return (char) returnValue;
}

void putc(char c) {
    __asm__ volatile("mv a1, %[a1]" : : [a1] "r"(c));
    __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(Code::putC));
    __asm__ volatile ("ecall");
}

