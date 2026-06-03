#include "riscv.h"

__attribute__ ((aligned (16))) char stack0[4096];

void mvec();
void main();

void start()
{
    // init trap handlar
    w_mtvec(mvec);

    // call main() in main.c
    main();
}