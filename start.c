#include "dev.h"
#include "riscv.h"

__attribute__((aligned(16))) char stack0[4096];

void main();

__attribute__((noreturn)) void
start()
{
    // init trap handler
    w_mtvec(mvec);

    // enable Machine External Interrupt
    w_mie(r_mie() | MIE_MEIE);

    // call main() in main.c
    main();

    // spin here
    while (1)
        ;
}
