TARGET  = firmware
CC      = riscv32-unknown-elf-gcc
OBJCOPY = riscv32-unknown-elf-objcopy

# 筆記： 距離算法 -mcmodel 很重要！ 你需要檢查那些距離你很遠的位置
CFLAGS  = -march=rv32imac_zicsr -mabi=ilp32 -mcmodel=medany \
          -fvisibility=hidden -nostdlib -nostartfiles \
          -static -Wno-int-conversion \
          -MMD -MF $@.d

LD      = thinking_board.ld
SRCS_C  = gpio.c main.c plic.c start.c trap.c
SRCS_S  = entry.S
OBJS    = $(SRCS_C:.c=.o) $(SRCS_S:.S=.o)
DEPS    = $(OBJS:.o=.o.d)

MOUNT   = /run/media/bongo/HiFive

all: $(TARGET).hex

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -T$(LD) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

flash: $(TARGET).hex
	cp $< $(MOUNT)

clean:
	rm -f *.o *.elf *.hex *.d

-include $(DEPS)