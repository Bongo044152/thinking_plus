        # placed at 0x20010000.
.section .text.init
.global _entry
_entry:
        # sp = stack0 + 4096
        la sp, stack0
        li t0, 4096
        add sp, sp, t0

        # jump to start() in start.c
        call start
spin:
        j spin
