// NOTE: 1 core mechine, single process

#include "plic.h"
#include "gpio.h"
#include "trap.h"
#include "uart.h"
#include "riscv.h"

void main()
{
    init_plic();
    init_gpio();
    init_trap();
    init_uart();

    __sync_synchronize();   // strong memory barrier

    // enable pin0 as start single
    gpio_output_enable(0);
    gpio_pin_lo(0);

    // interrupt on
    intr_on();

    // goto the wait mode
    while(1)
        asm volatile("wfi");
}
