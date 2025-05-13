# 1 "src/interrupt.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/riscv64-linux-gnu/include/stdc-predef.h" 1 3
# 32 "<command-line>" 2
# 1 "src/interrupt.S"
.align 4 #.balign ili .align
.global _ZN5Riscv9interruptEv
.type _ZN5Riscv9interruptEv, @function

.extern _ZN5Riscv12ecallHandlerEv
.extern _ZN5Riscv12timerHandlerEv
.extern _ZN5Riscv14consoleHandlerEv

_ZN5Riscv9interruptEv: #broji se od nulte instrukcije
    j environmentCall #0. instrukcija
    j timerFunction #1. instrukcija
    addi x0, x0, 1 #nema efekat
    addi x0, x0, 1
    addi x0, x0, 1
    addi x0, x0, 1
    addi x0, x0, 1
    addi x0, x0, 1
    addi x0, x0, 1
    j consoleFunction #9. instrukcija
    #sret #ne stize do njega

environmentCall: #ovde ne cuva registre jer se preko njih prosledjuju argumenti za sistemski poziv(a0-a7 su 10-17)
    addi sp, sp, -256 #pomera sp nagore; SP raste nanize i pokazuje na poslednji zauzeti; cuva sve registre
    .irp index, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 18, 19, 20, 21, 22, 23, 24, 25, 26,27, 28, 29, 30, 31
    sd x\index, \index * 8(sp)
    .endr

    call _ZN5Riscv12ecallHandlerEv

    .irp index, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 18, 19, 20, 21, 22, 23, 24, 25, 26,27, 28, 29, 30, 31 #breakpoint
    ld x\index, \index * 8(sp) #breakpoint
    .endr
    addi sp, sp, 256 #moze druga vrednost, posto ne koristi svih 256 bajtova
    sret


timerFunction:
    addi sp, sp, -256 #pomera sp nagore; SP raste nanize i pokazuje na poslednji zauzeti; cuva sve registre
    .irp index, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,27, 28, 29, 30, 31
    sd x\index, \index * 8(sp)
    .endr

    call _ZN5Riscv12timerHandlerEv

    .irp index, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,27, 28, 29, 30, 31 #breakpoint
    ld x\index, \index * 8(sp) #breakpoint
    .endr
    addi sp, sp, 256

    sret


consoleFunction:
    addi sp, sp, -256 #pomera sp nagore; SP raste nanize i pokazuje na poslednji zauzeti; cuva sve registre
    .irp index, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,27, 28, 29, 30, 31 #i ovde se potencijalno ne cuvaju svi registri
    sd x\index, \index * 8(sp)
    .endr

    call _ZN5Riscv14consoleHandlerEv

    .irp index, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,27, 28, 29, 30, 31
    ld x\index, \index * 8(sp)
    .endr
    addi sp, sp, 256
    sret
