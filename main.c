// NOTE: 1 core machine, single process

#include "dev.h"
#include "riscv.h"

__attribute__((noreturn)) void
main()
{
    init_plic();
    init_gpio();
    init_trap();
    init_uart();

    __sync_synchronize();  // memory barrier

    // enable pin0 as start signal
    gpio_output_enable(PIN_START_SIG);
    gpio_pin_lo(PIN_START_SIG);

    // interrupt on
    intr_on();

    // goto the waiting mode
    while (1)
        asm volatile("wfi");
}
