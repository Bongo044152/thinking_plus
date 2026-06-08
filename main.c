// NOTE: 1 core machine, single process

#include "gpio.h"
#include "plic.h"
#include "riscv.h"
#include "trap.h"
#include "uart.h"

int x;  // sbss?

__attribute__((noreturn)) void
main()
{
    init_plic();
    init_gpio();
    init_trap();
    init_uart();

    __sync_synchronize();  // memory barrier

    // enable pin0 as start signal
    gpio_output_enable(0);
    gpio_pin_lo(0);

    // interrupt on
    intr_on();

    // goto the wait mode
    while (1)
        asm volatile("wfi");
}
