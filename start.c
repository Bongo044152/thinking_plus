#include "riscv.h"

__attribute__ ((aligned (16))) char stack0[4096];

int x = 10;

void mvec();
void main();

void start()
{
    // init trap handlar
    w_mtvec(mvec);

    // ... ??
    x += 1;

    // call main() in main.c
    main();
}