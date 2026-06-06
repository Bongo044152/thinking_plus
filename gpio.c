#include "gpio.h"
#include "type.h"

void
init_gpio()
{
    // UART 控制目標：pin1, pin2
    const int pin_list[] = {1, 2};
    for (int i = 0; i < NELE(pin_list); ++i) {
        gpio_output_enable(pin_list[i]);
    }

    // for panic
    gpio_output_enable(23);
    gpio_pin_lo(23);  // init to low

    // route pin16/17 to UART0 via IOF0
    // pin16: UART0 RX, pin17: UART0 TX
    uint32 iof_en = IOF_EN;
    iof_en |= GPIO_PIN_MASK(16);
    iof_en |= GPIO_PIN_MASK(17);
    IOF_EN = iof_en;

    // NOTE: iof_sel remains zero (power-on reset default); IOF_SEL=0 selects
    // IOF0 (UART/SPI), IOF_SEL=1 selects IOF1 (PWM)
}
