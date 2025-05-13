//
// Created by os on 8/15/23.
//

//PREUZETO SA VEZBI

#ifndef PROJEKAT_SCHEDULER_HPP
#define PROJEKAT_SCHEDULER_HPP

#include "../h/list.hpp"

class TCB;

class Scheduler {
private:
    static List<TCB> readyThreadQueue;

public:
    static TCB *get();

    static void put(TCB *ccb);

};

#endif //PROJEKAT_SCHEDULER_HPP
