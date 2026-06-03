#ifndef GPIO_H
#define GPIO_H

#include "memory_layout.h"
#include "type.h"

#define NGPIO 32

// input_val:
// + Reading the input_val register returns the actual value of the pin gated by input_en.
// 
// input_val = real_input & input_en
#define GPIO_INPUT_VAL      (*(volatile uint32 *) GPIO_BASE)

#define GPIO_INPUT_EN       (*(volatile uint32 *)(GPIO_BASE + 0x04))
#define GPIO_OUTPUT_EN      (*(volatile uint32 *)(GPIO_BASE + 0x08))

// output_val:
// + Writing to the output_val register updates the bits
//      regardless of the tristate value.
// 
// + Reading the output_val register returns the written value.
#define GPIO_OUTPUT_VAL     (*(volatile uint32 *)(GPIO_BASE + 0x0c))

// interrupt
//  rise_ie = 0x1  -> pin 1 interrupt enable
//  rise_ip = 0x1  -> pin 1 has interrupt pending
// NOTE: Once the interrupt is pending, it will remain 
//   set until a 1 is written to the *_ip register at that bit.
//      ==> write-1-to-clear (W1C)

#define GPIO_RISE_IE        (*(volatile uint32 *)(GPIO_BASE + 0x18))
#define GPIO_RISE_IP        (*(volatile uint32 *)(GPIO_BASE + 0x1c))
#define GPIO_FALL_IE        (*(volatile uint32 *)(GPIO_BASE + 0x20))
#define GPIO_FALL_IP        (*(volatile uint32 *)(GPIO_BASE + 0x24))
#define GPIO_HIGH_IE        (*(volatile uint32 *)(GPIO_BASE + 0x28))
#define GPIO_HIGH_IP        (*(volatile uint32 *)(GPIO_BASE + 0x2c))
#define GPIO_LOW_IE         (*(volatile uint32 *)(GPIO_BASE + 0x30))
#define GPIO_LOW_IP         (*(volatile uint32 *)(GPIO_BASE + 0x34))

#define IOF_EN              (*(volatile uint32 *)(GPIO_BASE + 0x38))
#define IOF_SEL             (*(volatile uint32 *)(GPIO_BASE + 0x3C))

#define GPIO_PIN_MASK(pin_num)  (1 << pin_num)

// suggest SOP: claim -> copy *ip -> W1C -> handel -> complete

static inline void
gpio_pin_hi(const int pin_num)
{
    if(0 <= pin_num && pin_num < NGPIO) {
        GPIO_OUTPUT_VAL = GPIO_OUTPUT_VAL | GPIO_PIN_MASK(pin_num);
    }
}

static inline void
gpio_pin_lo(const int pin_num)
{
    if(0 <= pin_num && pin_num < NGPIO) {
        GPIO_OUTPUT_VAL = GPIO_OUTPUT_VAL & ~GPIO_PIN_MASK(pin_num);
    }
}

static inline void
gpio_pin_set(const int pin_num, const int v)
{
    if(0 <= pin_num && pin_num < NGPIO) {
        uint32 value = GPIO_OUTPUT_VAL;
        // 1. clear that bit
        value  = value & ~GPIO_PIN_MASK(pin_num);
        // 2. set that bit to `v`
        GPIO_OUTPUT_VAL = value | (v << pin_num);
    }
}

static inline void
gpio_output_enable(const int pin_num)
{
    if(0 <= pin_num && pin_num < NGPIO)
        GPIO_OUTPUT_EN |= GPIO_PIN_MASK(pin_num);
}

static inline void
gpio_output_disable(const int pin_num)
{
    if(0 <= pin_num && pin_num < NGPIO)
        GPIO_OUTPUT_EN &= ~GPIO_PIN_MASK(pin_num);
}

static inline void
gpio_input_enable(const int pin_num)
{
    if(0 <= pin_num && pin_num < NGPIO)
        GPIO_INPUT_EN |= GPIO_PIN_MASK(pin_num);
}

static inline void
gpio_input_disable(const int pin_num)
{
    if(0 <= pin_num && pin_num < NGPIO)
        GPIO_INPUT_EN &= ~GPIO_PIN_MASK(pin_num);
}

void init_gpio();

#endif // GPIO_H
