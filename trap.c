#include "dev.h"
#include "gpio.h"
#include "riscv.h"

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
    const uint32 mcause = r_mcause();
    if (mcause == 0x8000000B /* Machine External Interrupt */) {
        devintr();
    } else {
        // unknown trap
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
    gpio_pin_hi(PIN_PANIC_LED);
    while (1)
        ;  // spin ...
}
