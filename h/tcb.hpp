//
// Created by os on 8/16/23.
//

//PREUZETO SA VEZBI

#ifndef PROJEKAT_TCB_HPP
#define PROJEKAT_TCB_HPP

#include "../lib/hw.h"
#include "../h/scheduler.hpp"
#include "syscallHandler.hpp"

class TCB {
public:
    ~TCB() { if(stack!=0) SysCallHandler::memFree(stack); }

    bool isFinished() const { return finished; }

    void setFinished(bool value) { finished = value; }

    uint64 getTimeSlice() const { return timeSlice; }


    using Body = void (*)(void*);//pointer na funkciju sa argumentima
    static TCB *createThread(Body body, void* args);

    void setUserMode(bool mode) { userMode = mode; }//true ako je supervizorsko, false ako nije


    void* operator new(size_t size); //preklopljeni new
    void operator delete(void* p); //preklopljeni delete

    static TCB *running;

private://explicit sprecava konverziju argumenata
    explicit TCB(Body body, uint64 timeSlice, void* args) :
                body(body),
                stack(body != nullptr ? (uint64*) SysCallHandler::memAlloc(STACK_SIZE) : nullptr), //ako je glavni tok, onda mu ne treba stek, vec ga ima;
                context({ //ovako se mogu inicijalizovati strukture
                                (uint64) &TCB::threadWrapper,
                                stack != nullptr ? (uint64) &stack[STACK_SIZE] : 0 //vec ima stek; //stek ukazuje na poslednju lokaciju
                }),
                timeSlice(timeSlice),
                arguments(args),
                finished(false)
                {
        if(body != nullptr) Scheduler::put(this);

    }

    struct Context {
        uint64 ra; //return address; registar x1; reg x0 je hard-wired zero
        uint64 sp; //pointer na stek; registar x2
    };

    Body body;
    uint64 *stack;//pocetak oblasti memorije rezervisane za stek
    Context context;
    uint64 timeSlice;
    void* arguments;//argumenti sa kojima se pokrece data funkcija
    bool finished;

    bool userMode=Mode::USER_MODE;//kada je true, onda se nit pokrece u supervizorskom modu
    //bool paused=false;

    enum Mode {
        USER_MODE = 0,
        SUPERVISOR_MODE = 1
    };

    thread_t waitingToFinish = 0;//na koju ceka tekuca nit

    friend class Riscv; //da bi mogao da se pozove dispatch
    friend class SysCallHandler;
    friend class Sem;
    friend class Thread;

    static void threadWrapper();//uvek se izvrsava prvo threadWrapper pa onda body

    static void contextSwitch(Context *oldContext, Context *newContext);//menja kontekst(ra i sp registre)

    static void dispatch(); //vrsi promenu thread-a

    static uint64 timeSliceCounter;//staticko jer samo jedan thread radi u jednom trenutku

    static uint64 constexpr STACK_SIZE = DEFAULT_STACK_SIZE;//1024;//predefinisana velicina steka za jednu korutinu; treba DEFAULT_STACK_SIZE
    static uint64 constexpr TIME_SLICE = DEFAULT_TIME_SLICE;//2;//dve periode za izvrsavanje jedne niti; 10 puta u sekundi poziva timer; Treba DEFAULT_TIME_SLICE
};

#endif //PROJEKAT_TCB_HPP
