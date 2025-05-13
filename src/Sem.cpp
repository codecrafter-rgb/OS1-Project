//
// Created by os on 8/24/23.
//

#include "../h/Sem.hpp"
#include "../h/Riscv.hpp"


int Sem::wait() {
    volatile uint64 sstatus = Riscv::r_sstatus();//samo u privilegovanom rezimu //breakpoint
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);//clear-uje taj bit
    //lock();
    if(!closedPrematurely) {
        if (--val < 0) block();//breakpoint
    }
    //unlock();
    Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);//enable-uje interrupt ako je bio ukljucen
    return (closedPrematurely ? -1 : 0);//uspelo
}

int Sem::signal() {
    volatile uint64 sstatus = Riscv::r_sstatus();//samo u privilegovanom rezimu
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);//clear-uje taj bit

    if(++val<=0) unblock();//breakpoint

    Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);//enable-uje interrupt ako je bio ukljucen
    return 0;//uspelo
}

void Sem::block() {
    //mora u ecall-u;
    blocked.addLast(TCB::running);//breakpoint

    TCB *old = TCB::running;

    TCB::timeSliceCounter=0;
    TCB::running = Scheduler::get();//breakpoint

    TCB::contextSwitch(&old->context, &TCB::running->context);

}

void Sem::unblock() {
    TCB* t = blocked.removeFirst();
    Scheduler::put(t);
}

sem_t Sem::createSemaphore(unsigned init) {
    return new Sem(init);
}

int Sem::closeSemaphore(sem_t handle) {
    if(handle!=0) {
        handle->val = 0;
        handle->closedPrematurely = true;

        TCB *t;
        while ((t = handle->blocked.removeFirst()) != 0) {
            Scheduler::put(t);
        }
        return 0;
    }
    else return -1;//pointer pogresan
}


void* Sem::operator new(size_t size) {
    uint64 sizeInBlocks = (size+MEM_BLOCK_SIZE-1)/MEM_BLOCK_SIZE;//u sistemskom pozivu
    return (void*) SysCallHandler::memAlloc(sizeInBlocks);
}

void Sem::operator delete(void* p) {
    closeSemaphore((Sem*)p);
    SysCallHandler::memFree(p);
}


