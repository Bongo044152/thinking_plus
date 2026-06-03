#include "type.h"
#include "plic.h"

void init_plic(void)
{
    // disable interrupt
    *(uint32 *)PLIC_ENABLE_BASE = 0;
    *(uint32 *)(PLIC_ENABLE_BASE + 4) = 0;

    // setup priority threshold
    *(uint32 *)PLIC_THRESHILD = 0;
}

int claim(void)
{
    int irq = *(uint32 *)PLIC_SCLAIM;
    return irq;
}

void complete(int irq)
{
    *(uint32 *)PLIC_SCLAIM = irq;
}
