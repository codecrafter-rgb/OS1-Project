//
// Created by os on 8/16/23.
//

//PREUZETO SA VEZBI

#include "../h/Riscv.hpp"
#include "../lib/console.h"
#include "../h/tcb.hpp"
#include "../h/print.hpp"

#include "../h/syscall_c.h"
#include "../h/syscallHandler.hpp"

//mora da bude ne-inline
void Riscv::popSppSpie() {
    __asm__ volatile("csrw sepc, ra"); //ra je vec lokacija sa koje je pozvano popSppSpie(funkcija threadWrapper)
    if(!TCB::running->userMode) mc_sstatus(SSTATUS_SPP);
    else ms_sstatus(SSTATUS_SPP);
    __asm__ volatile("sret");
}


void Riscv::ecallHandler() {

    volatile uint64 scause = r_scause();
    volatile uint64 sepc = r_sepc() + 4;
    volatile uint64 sstatus = r_sstatus();

    if(scause == USER_ECALL || scause == SUPER_ECALL) {
        volatile uint64 code, par1, par2, par3, par4;
        __asm__ volatile("mv %[a0], a0" : [a0] "=r"(code));//kod sistemskog poziva
        __asm__ volatile("mv %[a1], a1" : [a1] "=r"(par1));//prvi parametar
        __asm__ volatile("mv %[a2], a2" : [a2] "=r"(par2));//drugi parametar
        __asm__ volatile("mv %[a3], a3" : [a3] "=r"(par3));//treci parametar
        __asm__ volatile("mv %[a4], a4" : [a4] "=r"(par4));//treci parametar
        volatile uint64 returnValue;
        switch(code) {
            case threadDispatch:
                SysCallHandler::threadDispatch();
                break;
            case memAlloc:
                returnValue=(uint64)SysCallHandler::memAlloc((size_t) par1);
                __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(returnValue)); //moze da se obrise, return value je uvek u a0
                break;
            case memFree:
                returnValue=(uint64) SysCallHandler::memFree((void*) par1);
                __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(returnValue));
                break;
            case threadCreate:
                SysCallHandler::threadCreate((thread_t*)par1, (void (*)(void *)) par2, (void*)par3);//returnValue
                break;
            case threadExit:
                SysCallHandler::threadExit();//returnValue
                break;
            case threadJoin:
                SysCallHandler::threadJoin((thread_t)par1);//return Value
                break;
            case semOpen:
                SysCallHandler::semOpen((sem_t*) par1, par2);//breakpoint
                break;
            case semClose:
                SysCallHandler::semClose((sem_t) par1);//breakpoint
                break;
            case semWait://returnValue
                SysCallHandler::semWait((sem_t)par1);//breakpoint
                break;
            case semSignal://returnValue
                SysCallHandler::semSignal((sem_t)par1);//breakpoint
                break;
            case timeSleep://returnValue
                //SysCallHandler::timeSleep(par1);
                break;
            case getC:
                returnValue=(uint64) SysCallHandler::getC();
                __asm__ volatile("mv a0, %[a0]" : : [a0] "r"(returnValue));
                break;
            case putC:
                SysCallHandler::putC((char)par1);
                break;

            default:
                SysPrintString("Unknown system call\n");
                break;
        }
    }
    else {//breakpoint
            //Treba prikazati exception i zaustaviti izvrsavanje?
            SysPrintString("\nException:\nscause:");//ugnjezdeni sistemski poziv
            SysPrintHex(r_scause());
            SysPrintString("\nStval:");
            SysPrintHex(r_stval());
            SysPrintString("\nsepc:");
            SysPrintHex(r_sepc());
    }
    w_sstatus(sstatus);
    w_sepc(sepc);
}

void Riscv::timerHandler() {
    TCB::timeSliceCounter++;
    if(TCB::timeSliceCounter >= TCB::running->getTimeSlice()) {
        volatile uint64 sepc = r_sepc();
        volatile uint64 sstatus = r_sstatus();
        TCB::timeSliceCounter=0;                    //ispocetka broji
        TCB::dispatch();
        w_sstatus(sstatus);
        w_sepc(sepc);//pamti da bi mogao uopste sret da se vrati na odgovarajuce mesto sa odgovorajucim statusom //breakpoint
    }
    mc_sip(SIP_SSIP);
}

void Riscv::consoleHandler() { //treba clear SIP i ovde
    volatile uint64 scause = r_scause();
    if(scause == Cause::CONSOLE_INTR)
        console_handler();//on cita sa konzole
}


void Riscv::SysPrintString(const char *string) {
    uint64 sstatus = Riscv::r_sstatus();//u supervizorskom modu
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
    while(*string != '\0') {
        __putc(*string);//ovde treba putC; __putc//ovo jeste sistemski poziv
        string++;
    }
    Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);
}

void Riscv::SysPrintInteger(uint64 integer) {
    uint64 sstatus = Riscv::r_sstatus();
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
    static char digits[] = "0123456789"; //moguce vrednosti
    char buf[16];
    int i, neg;
    uint64 x;

    neg = 0;
    if(integer < 0) { //integer je uint64, uvek unsigned?
        neg = 1;
        x = -integer;
    } else { x=integer; }

    i=0;
    do {
        buf[i++] = digits[x % 10];
    } while( (x /= 10) != 0);
    if(neg)
        buf[i++] = '-';

    while(--i >= 0)
        __putc(buf[i]);//__putc
    Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);
}

void Riscv::SysPrintHex(uint64 integer) {
    uint64 sstatus = Riscv::r_sstatus();
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
    static char digits[] = "0123456789ABCDEF"; //moguce vrednosti
    char buf[16];
    int i;//, neg;
    uint64 x = integer;

    i=0;
    do {
        buf[i++] = digits[x % 16];
        x=x/16;
    } while( i != 16); // da bi print-ovalo 16 cifara sa leading-zeroes

    while(--i >= 0)
        __putc(buf[i]);//__putc
    Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);
}