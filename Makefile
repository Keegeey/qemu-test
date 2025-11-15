# Cortex-M3 bare metal project
TARGET = firmware

# Tools
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size

# Compiler flags for Cortex-M3
CFLAGS = -mcpu=cortex-m3 \
         -mthumb \
         -mfloat-abi=soft \
         -nostartfiles \
         -ffreestanding \
         -Wall \
         -Wextra \
         -O0 \
         -g

LDFLAGS = -T linker.ld

# Source files
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ_DIR = build
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Generate disassembly
disasm: $(TARGET).elf
	$(OBJDUMP) -d $< > $(TARGET).s

# Run in QEMU (hardware emulator)
qemu: $(TARGET).elf
	qemu-system-arm -M lm3s6965evb -nographic -kernel $<

# Debug with GDB
debug: $(TARGET).elf
	qemu-system-arm -M lm3s6965evb -nographic -kernel $< -s -S &
	gdb-multiarch -ex "target remote :1234" -ex "layout src" $<

clean:
	rm -rf $(OBJ_DIR) $(TARGET).elf $(TARGET).bin $(TARGET).s

.PHONY: all clean qemu debug disasm
