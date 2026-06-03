#ifndef RISCV_H
#define RISCV_H

#include "type.h"
#include "memory_layout.h"

// copy from xv6: 
//  https://github.com/mit-pdos/xv6-riscv

#ifndef __ASSEMBLER__

// which hart (core) is this?
static inline uint32
r_mhartid()
{
  uint32 x;
  asm volatile("csrr %0, mhartid" : "=r" (x) );
  return x;
}

// Machine Status Register, mstatus

#define MSTATUS_MPP_MASK (3 << 11) // previous mode.
#define MSTATUS_MPP_M (3 << 11)
// #define MSTATUS_MPP_S (1 << 11)
#define MSTATUS_MPP_U (0 << 11)

#define MSTATUS_MIE  (1 << 3)
#define MSTATUS_MPIE (1 << 7)

static inline uint32
r_mstatus()
{
  uint32 x;
  asm volatile("csrr %0, mstatus" : "=r" (x) );
  return x;
}

static inline void 
w_mstatus(uint32 x)
{
  asm volatile("csrw mstatus, %0" : : "r" (x));
}

// Machine-mode Interrupt Enable

#define MIE_SEIE (1L << 11) // external
#define MIE_STIE (1L << 7)  // timer

static inline uint32
r_mie()
{
  uint32 x;
  asm volatile("csrr %0, mie" : "=r" (x) );
  return x;
}

static inline void 
w_mie(uint32 x)
{
  asm volatile("csrw mie, %0" : : "r" (x));
}

// Machine-mode Trap-Vector Base Address
// low two bits are mode. (Direct mode)

static inline void 
w_mtvec(uint32 x)
{
  asm volatile("csrw mtvec, %0" : : "r" (x));
}

static inline uint32
r_mtvec()
{
  uint32 x;
  asm volatile("csrr %0, mtvec" : "=r" (x) );
  return x;
}

// Machine-mode Comparison Register

static inline uint64
r_mtimecmp()
{
  return *(volatile uint64 *)MTIMECMP;
}

static inline void 
w_mtimecmp(uint64 cmp_v)
{
  // ref:
  // - https://lkml.iu.edu/hypermail/linux/kernel/2601.0/01803.html
  // - https://docs.riscv.org/reference/isa/priv/machine.html#3-1-2-machine-level-memory-mapped-registers
  uint32 *mtimecmp = (uint32 *)MTIMECMP;
  
  uint32 bound = -1;    // 0xfff...
  *mtimecmp = bound;    // no smaller than old value
  uint32 lo = (uint32)cmp_v, hi = cmp_v >> 32;
  *(mtimecmp + 1) = hi; // no smaller than new value
  *mtimecmp = lo;
}

static inline uint64
r_mtime()
{
  // ref: https://docs.riscv.org/reference/isa/priv/machine.html#3-1-2-machine-level-memory-mapped-registers
  uint32 hi = 1, lo;
  uint32 hi_again = 0;
  while(hi != hi_again) {
    asm volatile("csrr %0, timeh" : "=r" (hi) );
    asm volatile("csrr %0, time" : "=r" (lo) );
    asm volatile("csrr %0, timeh" : "=r" (hi_again) );
    // 避免讀 lo 的時候進位，導致數值錯誤
  }

  return ((uint64)hi << 32) | lo;
}

// Machine-mode Trap Cause
static inline uint32
r_mcause()
{
  uint32 x;
  asm volatile("csrr %0, mcause" : "=r" (x) );
  return x;
}

// Machine-mode Trap Value
static inline uint32
r_mtval()
{
  uint32 x;
  asm volatile("csrr %0, mtval" : "=r" (x) );
  return x;
}

// enable device interrupts
static inline void
intr_on()
{
  w_mstatus(r_mstatus() | MSTATUS_MIE);
}

// disable device interrupts
static inline void
intr_off()
{
  w_mstatus(r_mstatus() & ~MSTATUS_MIE);
}

// are device interrupts enabled?
static inline int
intr_get()
{
  uint32 x = r_mstatus();
  return (x & MSTATUS_MIE) != 0;
}

static inline uint32
r_sp()
{
  uint32 x;
  asm volatile("mv %0, sp" : "=r" (x) );
  return x;
}

// // read and write tp, the thread pointer, which xv6 uses to hold
// // this core's hartid (core number).
// static inline uint32
// r_tp()
// {
//   uint32 x;
//   asm volatile("mv %0, tp" : "=r" (x) );
//   return x;
// }

// static inline void 
// w_tp(uint32 x)
// {
//   asm volatile("mv tp, %0" : : "r" (x));
// }

static inline uint32
r_ra()
{
  uint32 x;
  asm volatile("mv %0, ra" : "=r" (x) );
  return x;
}

#endif // __ASSEMBLER__

#endif  // RISCV_H