# Cortex-M4 bare metal project
TARGET = firmware

# Tools
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size

# Compiler flags for Cortex-M4
CFLAGS = -mcpu=cortex-m4 \
         -mthumb \
         -mfloat-abi=soft \
         -nostdlib \
         -nostartfiles \
         -ffreestanding \
         -Wall \
         -Wextra \
         -O0 \
         -g

LDFLAGS = -T linker.ld

# Source files
SRCS = src/startup.c src/main.c src/uart.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

disasm: $(TARGET).elf
	$(OBJDUMP) -d $< > $(TARGET).disasm

# Emulate firmware
qemu: $(TARGET).elf
	qemu-system-arm -M lm3s6965evb -nographic -kernel $<

debug: $(TARGET).elf
	qemu-system-arm -M lm3s6965evb -nographic -kernel $< -s -S &
	gdb-multiarch -ex "target remote :1234" -ex "layout src" $<

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin $(TARGET).disasm

.PHONY: all clean qemu debug disasm