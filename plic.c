#include "plic.h"
#include "type.h"

// Datasheet §10.2 Table 24
#define UART0_IRQ    3

void
init_plic(void)
{
    // disable all interrupt
    *(uint32 *) PLIC_ENABLE_BASE = 0;
    *(uint32 *) (PLIC_ENABLE_BASE + 4) = 0;

    // setup priority threshold
    *(uint32 *) PLIC_THRESHILD = 0;  // handle all interrupt

    /*             UART0 interrupt             */

    *(uint32 *) PLIC_ENABLE_BASE = *(uint32 *)PLIC_ENABLE_BASE | (1 << UART0_IRQ);
    PLIC_SOURCE_PRIORITY(UART0_IRQ) = 1;
}

uint32
plic_claim(void)
{
    uint32 irq = *(volatile uint32 *) PLIC_MCLAIM;
    return irq;
}

void
plic_complete(int irq)
{
    *(volatile uint32 *) PLIC_MCLAIM = irq;
}
