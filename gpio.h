#ifndef GPIO_H
#define GPIO_H

#include "memory_layout.h"
#include "type.h"

#define NGPIO 32

// input_val:
// + Reading the input_val register returns the actual value of the pin gated by input_en.
// 
// input_val = real_input & input_en
#define GPIO_INPUT_VAL      (*(uint32 *) GPIO_BASE)

#define GPIO_INPUT_EN       (*(uint32 *)(GPIO_BASE + 0x04))
#define GPIO_OUTPUT_EN      (*(uint32 *)(GPIO_BASE + 0x08))

// output_val:
// + Writing to the output_val register updates the bits
//      regardless of the tristate value.
// 
// + Reading the output_val register returns the written value.
#define GPIO_OUTPUT_VAL     (*(uint32 *)(GPIO_BASE + 0x0c))

// interrupt
//  rise_ie = 0x1  -> pin 1 interrupt enable
//  rise_ip = 0x1  -> pin 1 has interrupt pending
// NOTE: Once the interrupt is pending, it will remain 
//   set until a 1 is written to the *_ip register at that bit.
//      ==> write-1-to-clear (W1C)

#define GPIO_RISE_IE        (*(uint32 *)(GPIO_BASE + 0x18))
#define GPIO_RISE_IP        (*(uint32 *)(GPIO_BASE + 0x1c))
#define GPIO_FALL_IE        (*(uint32 *)(GPIO_BASE + 0x20))
#define GPIO_FALL_IP        (*(uint32 *)(GPIO_BASE + 0x24))
#define GPIO_HIGH_IE        (*(uint32 *)(GPIO_BASE + 0x28))
#define GPIO_HIGH_IP        (*(uint32 *)(GPIO_BASE + 0x2c))
#define GPIO_LOW_IE         (*(uint32 *)(GPIO_BASE + 0x30))
#define GPIO_LOW_IP         (*(uint32 *)(GPIO_BASE + 0x34))

#define IOF_EN              (*(uint32 *)(GPIO_BASE + 0x38))
#define IOF_SEL             (*(uint32 *)(GPIO_BASE + 0x3C))

#define GPIO_PIN_MASK(pin)  (1 << pin)

// suggest SOP: claim -> copy *ip -> W1C -> handel -> complete

static inline void
gpio_pin_hi(int pin)
{
    if(0 <= pin && pin <= 31) {
        GPIO_OUTPUT_VAL = GPIO_OUTPUT_VAL | GPIO_PIN_MASK(pin);
    }
}

static inline void
gpio_pin_lo(int pin)
{
    if(0 <= pin && pin <= 31) {
        GPIO_OUTPUT_VAL = GPIO_OUTPUT_VAL & ~GPIO_PIN_MASK(pin);
    }
}

static inline void
gpio_output_enable(int pin)
{
    if(0 <= pin && pin <= 31)
        GPIO_OUTPUT_EN |= GPIO_PIN_MASK(pin);
}

static inline void
gpio_output_disable(int pin)
{
    if(0 <= pin && pin <= 31)
        GPIO_OUTPUT_EN &= ~GPIO_PIN_MASK(pin);
}

static inline void
gpio_input_enable(int pin)
{
    if(0 <= pin && pin <= 31)
        GPIO_INPUT_EN |= GPIO_PIN_MASK(pin);
}

static inline void
gpio_input_disable(int pin)
{
    if(0 <= pin && pin <= 31)
        GPIO_INPUT_EN &= ~GPIO_PIN_MASK(pin);
}

void init_gpio();

#endif // GPIO_H
