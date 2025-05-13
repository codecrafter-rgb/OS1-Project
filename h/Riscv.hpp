//
// Created by os on 8/15/23.
//

#ifndef PROJEKAT_RISCV_HPP
#define PROJEKAT_RISCV_HPP

//PREUZETO SA VEZBI

#include "../lib/hw.h"

class Riscv {

public:

    //get sstatus.spp and sstatus.spie bits; Supervisor Previous Privilege i Supervisor Previous Interrupt Enable
    static void popSppSpie();//bitno da bude u .cpp fajlu

    //push all onto stack
    static void pushRegisters();

    //pop all off stack
    static void popRegisters();

    //read register scause
    static uint64 r_scause();

    //write register scause
    static void w_scause(uint64 scause);

    //read register sepc
    static uint64 r_sepc();

    //write register sepc
    static void w_sepc(uint64 sepc);

    //read register stvec
    static uint64 r_stvec();

    //write register stvec
    static void w_stvec(uint64 stvec);

    //read register stval
    static uint64 r_stval();

    //write register stval
    static void w_stval(uint64 stval);

    enum BitMaskSip {
        SIP_SSIP = (1 << 1),
        SIP_STIP = (1 << 5),
        SIP_SEIP = (1 << 9),
    };

    //mask set register sip
    static void ms_sip(uint64 mask);

    //mask clear register sip
    static void mc_sip(uint64 mask);

    //read register sip
    static uint64 r_sip();

    //write register sip
    static void w_sip(uint64 sip);

    enum BitMaskSstatus {
        SSTATUS_SIE = (1 << 1), //0 maskira spoljasnji prekid, ne u korisnickom
        SSTATUS_SPIE = (1 << 5), //previous SIE
        SSTATUS_SPP = (1 << 8), //iz kog rezima je skok; 0 -korisnicki
    };

    //mask set register sstatus
    static void ms_sstatus(uint64 mask);

    //mask clear register sstatus
    static void mc_sstatus(uint64 mask);

    //read register sstatus
    static uint64 r_sstatus();

    //write register sstatus
    static void w_sstatus(uint64 sstatus);

    //supervisor trap
    static void supervisorTrap(); //poziva se prilikom prekida

    //interrupt function
    static void interrupt();

    enum Cause {
        USER_ECALL = 0x0000000000000008,//ecall iz korisnickog rezima; UL ili ne?
        SUPER_ECALL = 0x0000000000000009,//ecall iz supervizorskog rezima
        SOFT_INTR = 0x8000000000000001, //supervisor software interrupt(za timer)
        CONSOLE_INTR = 0x8000000000000009 //konzola
    };

    //menja sstatus radi pokretanja iz userMode-a
    //static void userMode();

private:

    //ecall handler
    static void ecallHandler();
    //hardware handler(timer)
    static void timerHandler();
    //console handler
    static void consoleHandler();

    //supervisor trap handler
    static void handleSupervisorTrap();

    //za print-ovanje unutar interrupt handler-a
    static void SysPrintString(const char* string);
    static void SysPrintInteger(uint64 integer);
    static void SysPrintHex(uint64 integer);

};

inline uint64 Riscv::r_scause() {
    uint64 volatile scause;
    __asm__ volatile ("csrr %[scause], scause" : [scause] "=r"(scause));
    return scause;
}

inline void Riscv::w_scause(uint64 scause) {
    __asm__ volatile ("csrw scause, %[scause]" : : [scause] "r"(scause));
}

inline uint64 Riscv::r_sepc() {
    uint64 volatile sepc;
    __asm__ volatile ("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
    return sepc;
}

inline void Riscv::w_sepc(uint64 sepc) {
    __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc)); //??greska??
}

inline uint64 Riscv::r_stvec() {
    uint64 volatile stvec;
    __asm__ volatile ("csrr %[stvec], stvec" : [stvec] "=r"(stvec));
    return stvec;
}

inline void Riscv::w_stvec(uint64 stvec) {
    __asm__ volatile("csrw stvec, %[stvec]" : : [stvec] "r"(stvec));
}

inline uint64 Riscv::r_stval()
{
    uint64 volatile stval;
    __asm__ volatile ("csrr %[stval], stval" : [stval] "=r"(stval));
    return stval;
}

inline void Riscv::w_stval(uint64 stval)
{
    __asm__ volatile ("csrw stval, %[stval]" : : [stval] "r"(stval));
}

inline void Riscv::ms_sip(uint64 mask) {
    __asm__ volatile ("csrs sip, %[mask]" : : [mask] "r"(mask));
}

inline void Riscv::mc_sip(uint64 mask)
{
    __asm__ volatile ("csrc sip, %[mask]" : : [mask] "r"(mask));
}

inline uint64 Riscv::r_sip() {
    uint64 volatile sip;
    __asm__ volatile("csrr %[sip], sip" : [sip] "=r"(sip));
    return sip;
}

inline void Riscv::w_sip(uint64 sip) {
    __asm__ volatile ("csrw sip, %[sip]" : : [sip] "r"(sip));
}

inline void Riscv::ms_sstatus(uint64 mask) {
    __asm__ volatile ("csrs sstatus, %[mask]" : : [mask] "r"(mask)); //kako csrs, csrc
}

inline void Riscv::mc_sstatus(uint64 mask) {
    __asm__ volatile ("csrc sstatus, %[mask]" : : [mask] "r"(mask));
}


inline uint64 Riscv::r_sstatus() {
    uint64 volatile sstatus;
    __asm__ volatile ("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));
    return sstatus;
}

inline void Riscv::w_sstatus(uint64 sstatus) {
    __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
}

#endif //PROJEKAT_RISCV_HPP
