#include "trap.h"
#include "gpio.h"
#include "plic.h"
#include "riscv.h"
#include "uart.h"

void
init_trap()
{
    // nothing to do ...
}

int devintr(void);

__attribute__((interrupt("machine"))) void
mvec()
{
    // handel interrupt
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

    if (irq == 3 /* UART0 */) {
        uartintr();
        plic_complete(irq);
        return irq;
    }
    return 0;
}

__attribute__((noreturn)) void
panic(void)
{
    gpio_output_enable(23);
    gpio_pin_hi(23);
    while (1)
        ;  // spin ...
}
