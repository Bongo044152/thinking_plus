        # placed at 0x20010000.
.section .text.init
.global _entry
_entry:
        # stack0 defined at start.c
        # sp = stack0 + 4096
        la sp, stack0
        li t0, 4096
        add sp, sp, t0
crt:
init_bss:
        la t0, __bss_start
        la t1, __bss_end
L1:
        beq t0, t1, init_data
        sw zero, 0(t0)
        addi t0, t0, 4
        j L1
init_data:
        la t0, __data_start
        la t1, __data_end
        la t2, __data_load      # load from flash memory (RO)
L2:
        beq t0, t1, call_start
        lw t3, 0(t2)
        sw t3, 0(t0)
        addi t0, t0, 4
        addi t2, t2, 4
        j L2
call_start:
        # jump to start() in start.c
        call start

# Never Return !!!
spin:
        j spin
