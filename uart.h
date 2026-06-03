// github reference code:
// https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/uart.c

#ifndef UART_H
#define UART_H

#include "memory_layout.h"

void init_uart(void);

void uartputc_sync(char c);

int uart_putc(char c);  // immediately put, return 1 when accept

int uartgetc(char *ch);

void uartintr(void);

#endif  // UART_H