NASM    = nasm
CC      = gcc
LD      = ld
QEMU    = qemu-system-i386

NASMFLAGS  = -f elf32
CFLAGS     = -m32 -O2 -ffreestanding -Wall -Wextra -fno-builtin -fno-exception -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs
LDFLAGS    = -m elf_i386 --nmagic -T linker.ld

SRC_DIR    = src
BUILD_DIR  = build
BOOT_DIR   = boot

ASM_SRCS   = $(SRC_DIR)/boot.asm

C_SRCS     = $(SRC_DIR)/kernel.c

ASM_OBJS   = $(ASM_SRCS:$(SRC_DIR)/%.asm=$(BUILD_DIR)/%.o)
C_OBJS     = $(C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
# OBJS       = $(ASM_OBJS) 
OBJS       = $(ASM_OBJS) $(C_OBJS)

KERNEL     = $(BOOT_DIR)/kernel.elf
IMAGE	   = disk.img

all: image

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm | $(BUILD_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

image: $(KERNEL)
	sudo sh ./disk-builder.sh

run:
	$(QEMU) -drive file=$(IMAGE),format=raw,

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(MNT_POINT)
	rm -f $(KERNEL)

fclean: clean
	rm -f $(IMAGE)

re: fclean all

.PHONY: all clean fclean re run