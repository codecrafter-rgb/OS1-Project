//
// Created by os on 8/20/23.
//

#ifndef PROJEKAT_SYSCALL_C_H
#define PROJEKAT_SYSCALL_C_H

#include "../lib/hw.h"

//using size_t = decltype(sizeof(0));

void * mem_alloc(size_t size);

int mem_free(void*);


class TCB;//_thread
typedef TCB _thread;
typedef _thread* thread_t;

int thread_create( thread_t* handle, void(*start_routine)(void*), void* arg);

int thread_exit();

void thread_dispatch();

void thread_join(thread_t handle);

class Sem;//dodato
typedef Sem _sem;
typedef _sem* sem_t;

int sem_open ( sem_t* handle, unsigned init);

int sem_close(sem_t handle);

int sem_wait(sem_t id);

int sem_signal(sem_t id);

typedef unsigned long time_t;

int time_sleep(time_t);

const int EOF = -1;

char getc();

void putc(char);

//code u ABI
enum Code {
    memAlloc = 0x01,
    memFree = 0x02,
    threadCreate = 0x11,
    threadExit = 0x12,
    threadDispatch = 0x13,
    threadJoin = 0x14,
    semOpen = 0x21,
    semClose = 0x22,
    semWait = 0x23,
    semSignal = 0x24,
    timeSleep = 0x31,
    getC = 0x41,
    putC = 0x42,
};

#endif //PROJEKAT_SYSCALL_C_H
