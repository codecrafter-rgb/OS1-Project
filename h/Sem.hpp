//
// Created by os on 8/24/23.
//
//DELIMICNO PREUZETO SA KOLOKVIJUMA

#ifndef PROJEKAT_SEM_HPP
#define PROJEKAT_SEM_HPP

#include "tcb.hpp"

class Sem {
public:
    static sem_t createSemaphore(unsigned init);
    static int closeSemaphore(sem_t handle);

    int wait();
    int signal();

    int value() const { return val; }

    void* operator new(size_t size); //preklopljeni new
    void operator delete(void* p); //preklopljeni delete

protected:
    void block();
    void unblock();

private:
    Sem(unsigned int init) : val(init), lock(0) {
        closedPrematurely=false;
    }

    ~Sem() {
        
    }
    int val, lock;
    List<TCB> blocked;
    bool closedPrematurely=false;

};

#endif //PROJEKAT_SEM_HPP
