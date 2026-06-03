// NOTE: 1 core mechine, single process

#include "plic.h"
#include "gpio.h"
#include "trap.h"

int is_little_endian(void) {
    union {
        uint32 i;
        uint8  b[4];
    } u = { .i = 0x01020304 };
    return u.b[0] == 0x04;
}

void main()
{
    init_plic();
    init_gpio();
    init_trap();

    __sync_synchronize();   // strong memory barrier

    // enable pin0
    gpio_output_enable(0);
    // light up led at pin0
    if(is_little_endian()) {
        gpio_pin_lo(0);
    }
    else {
        gpio_pin_hi(0);
    }

    // goto wait mode
    while(1)
        asm volatile("wfi");
}
