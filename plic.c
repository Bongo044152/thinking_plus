#include "board.h"
#include "memory_layout.h"
#include "type.h"

// value: 7(hi) ~ 1(low), 0 = no interrupt
#define PLIC_SOURCE_PRIORITY(id) (*(uint32 *) (PLIC + 4 * (id)))
#define PLIC_ENABLE_BASE (PLIC + 0x2000)

// value: 7 ~ 0
// context 0 = M-mode hart 0 (the only context on FE310)
#define PLIC_THRESHILD (PLIC + 0x200000)
#define PLIC_MCLAIM (PLIC + 0x200004)

void
init_plic(void)
{
    // disable all interrupt
    *(uint32 *) PLIC_ENABLE_BASE = 0;
    *(uint32 *) (PLIC_ENABLE_BASE + 4) = 0;

    // setup priority threshold
    *(uint32 *) PLIC_THRESHILD = 0;  // handle all interrupt

    /*             UART0 interrupt             */

    *(uint32 *) PLIC_ENABLE_BASE =
        *(uint32 *) PLIC_ENABLE_BASE | (1 << UART0_IRQ);
    PLIC_SOURCE_PRIORITY(UART0_IRQ) = 1;
}

uint32
plic_claim(void)
{
    const uint32 irq = *(volatile uint32 *) PLIC_MCLAIM;
    return irq;
}

void
plic_complete(int irq)
{
    *(volatile uint32 *) PLIC_MCLAIM = irq;
}
