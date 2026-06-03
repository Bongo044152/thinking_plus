#include "gpio.h"
#include "type.h"

void
init_gpio()
{
    // init pin
    const int pin_list[] = {1, 2, 9, 10, 11};
    for (int i = 0; i < NELE(pin_list); ++i) {
        gpio_output_enable(pin_list[i]);
    }

    // uart debug pin
    gpio_output_enable(22);
    gpio_pin_lo(22);

    // enable io function port at specific port 16, 17
    // 16: UART0 RX
    // 17: UART0 TX
    uint32 iof_en = IOF_EN;
    iof_en |= GPIO_PIN_MASK(16);
    iof_en |= GPIO_PIN_MASK(17);
    IOF_EN = iof_en;

    // NOTE: iof_sel remains zero
}
