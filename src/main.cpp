//
// Created by Luka on 8/13/23.
//

//#include "../lib/console.h"
#include "../h/tcb.hpp"


#include "../h/Riscv.hpp"
#include "../h/syscall_c.h"
#include "../lib/console.h"

#include "../test/printing.hpp"
#include "../h/syscall_cpp.hpp"

extern void userMain();

int main() {

    Riscv::w_stvec((uint64) &Riscv::interrupt | 1);

    TCB* threads[2];
    thread_create(&threads[0], nullptr, nullptr);
    TCB::running = threads[0];


    thread_create(&threads[1], (void (*)(void *)) (userMain), nullptr);
    threads[1]->setUserMode(false);//u korisnickom modu je

    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);

    thread_join(threads[1]);

    while(!(threads[1]->isFinished())){
        thread_dispatch();
    }

    return 0;
}

