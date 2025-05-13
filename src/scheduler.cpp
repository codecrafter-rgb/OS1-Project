//
// Created by os on 8/15/23.
//

//PREUZETO SA VEZBI

#include "../h/scheduler.hpp"

List<TCB> Scheduler::readyThreadQueue; // zove default-ni konstruktor

TCB *Scheduler::get() {
    return readyThreadQueue.removeFirst();//skida sa pocetka reda spremnih
}

void Scheduler::put(TCB *tcb) {
    readyThreadQueue.addLast(tcb);//stavlja na kraj reda cekanja
}
