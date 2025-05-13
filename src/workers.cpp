//
// Created by os on 8/15/23.
//

//Za testiranje rada korutina
//Preuzeto sa vezbi

/*#include "../lib/hw.h"
#include "../h/tcb.hpp"//jos nije implementirano
#include "../h/print.hpp"
#include "../h/syscall_c.h"//da li sme ovde


static uint64 fibonacci(uint64 n) {
    if(n==0 || n==1) { return n; }
    if( n % 4 ==0 ) thread_dispatch();//TCB::yield(); //daje nekome drugom kontrolu, pauzira izvrsavanje
    return fibonacci(n-1) + fibonacci(n-2);
}

//static sem_t sem_n;

void workerBodyA() {
    //sem_open(&sem_n, 1);

    //sem_wait(sem_n);
    //printString("workerA zakljucao semafor");
    for(uint64 i=0; i<10; i++) {
        printString("A: i=");
        printInteger(i);
        printString("\n");



        for(uint64 j=0; j<10000; j++)
        {
            for(uint64 k=0; k<30000; k++)
            {
                //busy wait
            }
            //TCB::yield();
        }
    }
    //sem_signal(sem_n);
    //printString("workerA oslobodio semafor");
}

//uporediti
void workerBodyB() {
    //sem_wait(sem_n);
    //printString("workerB propusten na semaforu");
    for(uint64 i=0; i<16; i++) {
        printString("B: i=");
        printInteger(i);
        printString("\n");



        for(uint64 j=0; j<10000; j++)
        {
            for(uint64 k=0; k<30000; k++)
            {
                //busy wait
            }
            //TCB::yield();
        }


    }
    //sem_close(sem_n);
    //sem_signal(sem_n);
    //printString("workerB oslobodio semafor");
}


void workerBodyC() {
    //sem_wait(sem_n);
    //printString("workerC propusten na semaforu");

    uint8 i =0;
    for(; i<3; i++) {
        printString("A: i=");
        printInteger(i);
        printString("\n");
    }

    printString("A: yield\n");
    __asm__ ("li t1, 7");
    //TCB::yield();//TCB::yield
    thread_dispatch();

    uint64 t1 = 0;
    __asm__ ("mv %[t1], t1" : [t1] "=r"(t1));

    printString("A: t1");
    printInteger(t1);
    printString("\n");

    uint64 result = fibonacci(20);
    printString("A: fibonacci=");
    printInteger(result);
    printString("\n");

    for(; i< 6; i++) {
        printString("A: i=");
        printInteger(i);
        printString("\n");
    }


    //sem_signal(sem_n);
    //printString("workerC oslobodio semafor");

    TCB::running->setFinished(true);
    //TCB::yield();
    thread_dispatch();
}

void workerBodyD() {
    //sem_wait(sem_n);
    //printString("workerD propusten na semaforu");

    uint8 i = 10;
    for(; i<13; i++) {
        printString("B: i=");
        printInteger(i);
        printString("\n");
    }

    printString("B: yield\n");
    __asm__ ("li t1, 5");
    //TCB::yield();
    thread_dispatch();

    uint64 result = fibonacci(23);
    printString("A: fibonacci=");
    printInteger(result);
    printString("\n");

    for(; i<16; i++){
        printString("B: i=");
        printInteger(i);
        printString("\n");
    }
    //printString("workerD oslobodio semafor");
    //sem_signal(sem_n);

    TCB::running->setFinished(true);
    //TCB::yield();
    thread_dispatch();
}
*/