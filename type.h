#ifndef TYPE_H
#define TYPE_H

// copy from xv6:
//  https://github.com/mit-pdos/xv6-riscv

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// typedef uint64 pde_t;

#define NELE(arr) (sizeof(arr) / sizeof *(arr))

#endif  // TYPE_H
