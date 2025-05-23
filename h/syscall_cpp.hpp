//
// Created by os on 8/20/23.
//

#ifndef PROJEKAT_SYSCALL_CPP_HPP
#define PROJEKAT_SYSCALL_CPP_HPP

#include "syscall_c.h"

void* operator new(size_t);//::
void operator delete(void*);//::

class Thread {
public:
    Thread(void (*body)(void*), void* arg);
    virtual ~Thread();

    int start();

    void join();

    static void dispatch();
    static int sleep(time_t);

    //funkcija koja pokrece run
    static void runWrapper(void* thread);


protected:
    Thread();
    virtual void run() {}

private:
    thread_t myHandle;
    void (*body)(void*); void* arg;
};

class Semaphore {
public:
    Semaphore(unsigned init = 1);//po default-u otvoren
    virtual ~Semaphore();

    int wait();
    int signal();

private:
    sem_t myHandle;
};


class PeriodicThread : public Thread {
public:
    void terminate();

protected:
    PeriodicThread(time_t period);
    virtual void periodicActivation() {}

private:
    time_t period;
};

class Console {
public:
    static char getc();

    static void putc(char);
};

#endif //PROJEKAT_SYSCALL_CPP_HPP
