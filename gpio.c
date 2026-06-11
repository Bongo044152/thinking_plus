#include "gpio.h"
#include "board.h"

void
init_gpio()
{
    // output pins
    gpio_output_enable(PIN_UART_CONTROL);
    gpio_output_enable(PIN_PANIC_LED);

    // init all output pins low
    gpio_pin_lo(PIN_UART_CONTROL);
    gpio_pin_lo(PIN_PANIC_LED);

    // route pin16/17 to UART0 via IOF0
    // pin16: UART0 RX, pin17: UART0 TX
    uint32 iof_en = IOF_EN;
    iof_en |= GPIO_PIN_MASK(PIN_UART0_RX);
    iof_en |= GPIO_PIN_MASK(PIN_UART0_TX);
    IOF_EN = iof_en;

    // NOTE: iof_sel remains zero (power-on reset default); IOF_SEL=0 selects
    // IOF0 (UART/SPI), IOF_SEL=1 selects IOF1 (PWM)
}
