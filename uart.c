
#include "uart.h"
#include "gpio.h"
#include "trap.h"
#include "type.h"

// the UART control registers are memory-mapped
// at address UART0. this macro returns the
// address of one of the registers.
#define Reg(reg) ((volatile unsigned char *) (UART0 + (reg)))

#define ReadReg(reg) (*((volatile uint32 *) Reg(reg)))
#define WriteReg(reg, v) (*((volatile uint32 *) Reg(reg)) = (v))

// the UART control registers.
// some have different meanings for read vs write.
// see
// https://sifive.cdn.prismic.io/sifive/034760b5-ac6a-4b1c-911c-f4148bb2c4a5_fe310-g002-v1p5.pdf

#define THR 0x0                // Transmit data register
#define RHR 0x4                // Receive data register
#define TXC 0x8                // Transmit control register
#define TXC_EN 0x1             // Transmit enable
#define RXC 0x0c               // Receive control register
#define RXC_EN 0x1             // Receive enable
#define RXC_WL(x) ((x) << 16)  // Receive watermark level
#define IE 0x10                // UART interrupt enable
// #define IE_TXWM     0b01    // Transmit watermark interrupt enable
#define IE_RXWM 0b10  // Receive watermark interrupt enable
#define IP 0x14       // UART interrupt pending
#define DIV 0x18      // Baud rate divisor

void
init_uart(void)
{
    // disable interrupts.
    WriteReg(IE, 0x00);

    // set baud rate: tlclk = 16MHz
    // baud = tlclk / (DIV+1) = 16e6 / 139 = 115107 (預期 115200 ； 誤差 -0.08%)
    WriteReg(DIV, 138);

    // Transmit enable, 1 stop bit
    WriteReg(TXC, TXC_EN);

    // Receive enable, watermark level = 0
    WriteReg(RXC, RXC_EN | RXC_WL(0));

    // enable interrupts
    WriteReg(IE, IE_RXWM);
}

// Datasheet §18.4 — amoor.w is the recommended way to write txdata;
// the full-bit (bit31) of the returned old value indicates FIFO state.
// tries to enqueue char into TX FIFO
// returns 1 if accepted, 0 if FIFO full
int
uart_putc(char c)
{
    volatile uint32 *txdata = (uint32 *) Reg(THR);
    uint32 ret;
    asm volatile("amoor.w %0, %2, (%1)"
                 : "=r"(ret)
                 : "r"(txdata), "r"((uint32) c)
                 : "memory");
    return !((ret >> 31) & 1);  // 1 = full, char not accepted
}

// Datasheet §18.5
// tries to dequeue one char from RX FIFO
// returns 1 if got a byte, 0 if FIFO empty
int
uartgetc(char *ch)
{
    uint32 value = ReadReg(RHR);  // address: 0x10013004

    // if not empty
    if (!(value >> 31)) {
        *ch = (char) value;
        return 1;
    }
    return 0;
}

// blocks until the char is accepted by TX FIFO ("busy put")
void
uartputc_sync(char c)
{
    while (!uart_putc(c))
        ;
}

// UART0 interrupt handler.
// Receives one-byte commands from the remote to drive local GPIO pins.
//
// Message format: [ X(7:5) | port(4:1) | v(0) ]
//   port : GPIO pin number to set
//   v    : 1 = high, 0 = low
//   X    : don't care
//
// Accepted pins: 1, 2
void
uartintr(void)
{
    char command;

    // this interrupt fires only when RX FIFO has data, so the first getc should
    // succeed
    while (!uartgetc(&command))
        ;

    // unpack port and value from the byte
    int p = (int) ((command >> 1) & 0xf);
    int v = command & 1;

    // 只接受 pin1/pin2，沒 match 到一律 panic
    if (p == 1 || p == 2)
        gpio_pin_set(p, v);
    else
        panic();
}
