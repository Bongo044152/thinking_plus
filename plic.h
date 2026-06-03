#ifndef PLIC_H
#define PLIC_H

#include "memory_layout.h"
#include "type.h"

// value: 7(hi) ~ 1(low), 0 = no interrupt
#define PLIC_SOURCE_PRIORITY(id)    (*(uint32 *)(PLIC + 4 * (id)))
#define PLIC_ENABLE_BASE            (PLIC + 0x2000)

// value: 7 ~ 0
#define PLIC_THRESHILD              (PLIC + 0x200000)
#define PLIC_SCLAIM                 (PLIC + 0x200004)

void init_plic(void);
uint32 plic_claim(void);
void plic_complete(int irq);

#endif // PLIC_H