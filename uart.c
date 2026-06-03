
#include "type.h"
#include "uart.h"

// the UART control registers are memory-mapped
// at address UART0. this macro returns the
// address of one of the registers.
#define Reg(reg) ((volatile unsigned char *)(UART0 + (reg)))

#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

// the UART control registers.
// some have different meanings for read vs write.
// see https://sifive.cdn.prismic.io/sifive/034760b5-ac6a-4b1c-911c-f4148bb2c4a5_fe310-g002-v1p5.pdf

#define THR         0x0     // Transmit data register
#define RHR         0x4     // Receive data register
#define TXC         0x8     // Transmit control register
#define TXC_EN      0x1     // Transmit enable
#define RXC         0x0c    // Receive control register
#define RXC_EN      0x1     // Receive enable
#define RXC_WL    (4 << 16) // Receive watermark level
#define IE          0x10    // UART interrupt enable
// #define IE_TXWM     0b01    // Transmit watermark interrupt enable
#define IE_RXWM     0b10    // Receive watermark interrupt enable
#define IP          0x14    // UART interrupt pending
#define DIV         0x18    // Baud rate divisor

void
uartinit(void)
{
    // disable interrupts.
    WriteReg(IE, 0x00);

    // set baud rate.
    WriteReg(DIV, 1301);

    // Transmit enable, 1 stop bit
    WriteReg(TXC, TXC_EN);

    // Receive enable, watermark level = 4
    WriteReg(RXC, RXC_EN | RXC_WL);

    // enable interrupts
    WriteReg(IE, IE_RXWM);
}

// Datasheet 18.4
int uart_putc(char c) {
    volatile uint32 *txdata = (uint32 *)Reg(THR);
    uint32 ret;
    asm volatile("amoor.w %0, %2, (%1)"
        : "=r"(ret)
        : "r"(txdata), "r"((uint32)c)
        : "memory");
    return !((ret >> 31) & 1); // 1 = full, char not accepted
    // return 1 when successed, 0 otherwise
}

// Datasheet 18.5
// this function try to get char as much as possible
// return 1 read successed, 0 otherwise
int uartgetc(char *ch)
{
    uint32 value = ReadReg(RHR);

    // if not empty
    if(!(value >> 31)) {
        *ch = (char) value;
        return 1;
    }
    return 0;
}

// TODO:
#error "PLIC 要初始化"
