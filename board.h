#ifndef BOARD_H
#define BOARD_H

// -- GPIO -- //

#define PIN_START_SIG 0     // start single             (output)
#define PIN_UART_CONTROL 1  // control pin              (output)
#define PIN_UART0_RX 16     // IOF0 for UART0 RX        (IOF0)
#define PIN_UART0_TX 17     // IOF0 for UART0 TX        (IOF0)
#define PIN_PANIC_LED 23    // red LED on RED-V board   (output)

// -- IRQ -- //

// Datasheet §10.2 Table 24
#define UART0_IRQ 3

#endif // BOARD_H