#ifndef MEMORY_LAYOUT
#define MEMORY_LAYOUT

#define DEBUG 0x00  // to 0x0FFF

// Instruction Tightly Integrated Memory
#define ITIM 0x08000000  // to 0x0800_1FFF   (8 KiB)

#define PLIC 0x0C000000            // to 0x0FFF_FFFF
#define GPIO_BASE 0x10012000       // to 0x1001_2FFF
#define UART0 0x10013000           // to 0x1001_3FFF
#define QSPI0 0x10014000           // to 0x1001_4FFF
#define PWM0 0x10015000            // to 0x1001_5FFF
#define I2C0 0x10016000            // to 0x1001_6FFF
#define CLINT 0x02000000           // to 0x0200_FFFF
#define MTIMECMP (CLINT + 0x4000)  // mtimecmp locate at 0x2004000
#define MTIME (CLINT + 0xbff8)     // mtime    locate at 0x200bff8

#define QSPI0_FLASH 0x20000000  // to 0x3FFF_FFFF

// Data Tightly Integrated Memory
#define DTIM 0x80000000  // to 0x8000_3FFF   (16 KiB)

#endif  // MEMORY_LAYOUT
