//
// Created by os on 8/15/23.
//

//PREUZETO SA VEZBI

#include "../h/print.hpp"
#include "../lib/console.h"
#include "../h/Riscv.hpp"
#include "../h/syscall_c.h"

/*void printString(char const *string) { //pointer na konstantan char
    //uint64 sstatus = Riscv::r_sstatus(); //ne blokira prekide jer se izvrsava u korisnickom modu
    //Riscv::mc_sstatus(Riscv::SSTATUS_SIE);//clear-uje taj bit
    while(*string != '\0') {
        putc(*string);//ovde treba putC; __putc//ovo jeste sistemski poziv
        string++;
    }
    //Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);//enable-uje interrupt ako je bio ukljucen
}

void printInteger(uint64 integer) {
    //uint64 sstatus = Riscv::r_sstatus();
    //Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
    static char digits[] = "0123456789"; //moguce vrednosti
    char buf[16];
    int i, neg;
    uint x;

    neg = 0;
    if(integer < 0) { //integer je uint64, uvek unsigned?
        neg = 1;
        x = -integer;
    } else
    {
        x=integer;
    }

    i=0;
    do {
        buf[i++] = digits[x % 10];
    } while( (x /= 10) != 0);
    if(neg)
        buf[i++] = '-';

    while(--i >= 0)
        putc(buf[i]);//__putc
    //Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);//enable-uje interrupt ako je bio ukljucen
}

void printHex(uint64 integer) {
    //printuje u hex formatu sa leading-zeroes
    //uint64 sstatus = Riscv::r_sstatus();
    //Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
    static char digits[] = "0123456789ABCDEF"; //moguce vrednosti
    char buf[16];
    int i;//, neg;
    uint64 x = integer;//nije bilo uint64, zato nije ispisivalo

    i=0;
    do {
        buf[i++] = digits[x % 16];
        x=x/16;
    } while( i != 16); // da bi print-ovalo 16 cifara sa leading-zeroes
    //if(neg)
    //    buf[i++] = '-';

    while(--i >= 0)
        putc(buf[i]);//__putc
    //Riscv::ms_sstatus(sstatus & Riscv::SSTATUS_SIE ? Riscv::SSTATUS_SIE : 0);//enable-uje interrupt ako je bio ukljucen
}
*/