//
// Created by os on 8/24/23.
//

#include "../h/syscall_cpp.hpp"
#include "../h/syscall_c.h"
#include "../h/scheduler.hpp"
#include "../h/tcb.hpp"
#include "../h/Riscv.hpp"


Thread::Thread(void (*body)(void *), void *arg) {
    this->body = (void (*)(void *)) &body;
    this->arg = arg;
}

Thread::~Thread() {
    delete myHandle;
}

int Thread::start() {
    thread_create(&myHandle, this->body, this->arg);
    return 0;
}

void Thread::join() {
    thread_join(TCB::running);//ceka na zavrsetak tekuce niti
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t time) {
    //return time_sleep(time);
    return 0;
}

Thread::Thread() {
    body = (void(*)(void*)) &runWrapper;
    arg = this;
}

void Thread::runWrapper(void *thread) {
    Thread* thr = (Thread*) thread;
    thr->run();//za polimorfno ponasanje
}

char Console::getc() {
    return PROJEKAT_SYSCALL_C_H::getc();
}

void Console::putc(char c) {
    PROJEKAT_SYSCALL_C_H::putc(c);
}

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle, init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    return sem_wait(myHandle);
}

int Semaphore::signal() {
    return sem_signal(myHandle);
}
