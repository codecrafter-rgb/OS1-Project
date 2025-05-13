//
// Created by os on 8/23/23.
//

#ifndef PROJEKAT_SYSCALLHANDLER_HPP
#define PROJEKAT_SYSCALLHANDLER_HPP

#include "syscall_c.h"

class SysCallHandler {
public:

    static void * memAlloc(size_t size);

    static int memFree(void*);

    static int threadCreate( thread_t* handle, void(*start_routine)(void*), void* arg);

    static int threadExit();

    static void threadDispatch();

    static void threadJoin(thread_t handle);

    static int semOpen(sem_t* handle, unsigned init);

    static int semClose(sem_t handle);

    static int semWait(sem_t id);

    static int semSignal(sem_t id);

    static int timeSleep(time_t);

    static char getC();

    static void putC(char);

    //moze friend klasa Riscv, pa sve private
};

#endif //PROJEKAT_SYSCALLHANDLER_HPP
