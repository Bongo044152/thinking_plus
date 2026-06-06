#include "trap.h"
#include "gpio.h"
#include "plic.h"
#include "riscv.h"
#include "uart.h"

#define UART0_IRQ 3

void
init_trap()
{
    // nothing to do ...
}

int devintr(void);

__attribute__((interrupt("machine"))) void
mvec()
{
    // handle interrupt
    uint32 mcause;
    if ((mcause = r_mcause()) == 0x8000000B /* Machine External Interrupt */) {
        devintr();
    } else {
        panic();
    }
}

// device interrupt
// return interrupt source code
int
devintr(void)
{
    const uint32 irq = plic_claim();

    if (irq == UART0_IRQ) {
        uartintr();
        plic_complete(irq);
        return irq;
    }
    panic();
}

__attribute__((noreturn)) void
panic(void)
{
    gpio_pin_hi(23);
    gpio_pin_lo(0);
    while (1)
        ;  // spin ...
}
