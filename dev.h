#ifndef DEV_H
#define DEV_H

#include "board.h"
#include "type.h"

// -- GPIO -- //

#include "gpio.h"

// -- PLIC -- //

void init_plic(void);
uint32 plic_claim(void);
void plic_complete(const int irq);

// -- TRAP -- //

void init_trap(void);
void mvec(void);
void panic(void) __attribute__((noreturn));

// -- UART -- //

void init_uart(const uint64 uart);
void uartputc_sync(const uint64 uart, const char c);
int uart_putc(const uint64 uart,
              const char c);  // immediately put, return 1 when accept
int uartgetc(const uint64 uart, char *ch);
void uart0intr(void);

#endif  // DEV_H
