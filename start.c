#include "riscv.h"

#define MIE_MEIE (1 << 11)  // Machine External Interrupt Enable

__attribute__((aligned(16))) char stack0[4096];

void mvec();
void main();

void
start()
{
    // init trap handlar
    w_mtvec(mvec);

    // enable Machine External Interrupt
    w_mie(r_mie() | MIE_MEIE);

    // call main() in main.c
    main();
}