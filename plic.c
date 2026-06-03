#include "type.h"
#include "plic.h"

void init_plic(void)
{
    // disable interrupt
    *(uint32 *)PLIC_ENABLE_BASE = 0;
    *(uint32 *)(PLIC_ENABLE_BASE + 4) = 0;

    // setup priority threshold
    *(uint32 *)PLIC_THRESHILD = 0;  // handel all interrupt

    /*             UART0 interrupt             */

    // enable uart0 interrupt (for this cpu)
    *(uint32 *)PLIC_ENABLE_BASE = (1 << 3);

    // interrupt priority (for this cpu)
    PLIC_SOURCE_PRIORITY(3 /* UART0 source */) = 1;
}

uint32 plic_claim(void)
{
    uint32 irq = *(uint32 *)PLIC_SCLAIM;
    return irq;
}

void plic_complete(int irq)
{
    *(uint32 *)PLIC_SCLAIM = irq;
}
