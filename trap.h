#ifndef TRAP_H
#define TRAP_H

void init_trap(void);
void mvec(void);
void panic(void) __attribute__((noreturn));

#endif  // TRAP_H