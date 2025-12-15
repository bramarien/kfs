NASM    = nasm
CC      = gcc
LD      = ld
QEMU    = qemu-system-i386

NASMFLAGS  = -f elf32
CFLAGS     = -m32 -O2 -ffreestanding -Wall -Wextra -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -g
LDFLAGS    = -m elf_i386 --nmagic -T linker.ld

SRC_DIR    = src
HDR_DIR    = inc
BUILD_DIR  = build
BOOT_DIR   = boot
LIBFT_DIR  = libft

HDRS       = $(HDR_DIR)/libft.h \
			 $(HDR_DIR)/keyboard.h \
	     		 $(HDR_DIR)/multiboot2.h \
			 $(HDR_DIR)/kfs.h

ASM_SRCS   = $(SRC_DIR)/boot.asm \
			 $(SRC_DIR)/keyboard_polling.asm

C_SRCS     = $(SRC_DIR)/kernel.c \
			 $(SRC_DIR)/keyboard.c \
			 $(SRC_DIR)/multiboot2.c
			 

ASM_OBJS   = $(ASM_SRCS:$(SRC_DIR)/%.asm=$(BUILD_DIR)/%.o)
C_OBJS     = $(C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
# OBJS       = $(ASM_OBJS) 
OBJS       = $(ASM_OBJS) $(C_OBJS)
LIBFT      = $(LIBFT_DIR)/libft.a

KERNEL     = $(BOOT_DIR)/kernel.elf
IMAGE	   = disk.img

all: image

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm | $(BUILD_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(HDR_DIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(KERNEL): $(OBJS) $(LIBFT)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBFT)

image: $(KERNEL)
	sudo sh ./disk-builder.sh

run:
	$(QEMU) -drive file=$(IMAGE),format=raw -vga std

debug:
	$(QEMU) -drive file=$(IMAGE),format=raw, -S -s -vga std

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(BUILD_DIR)
	rm -rf $(MNT_POINT)
	rm -f $(KERNEL)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(IMAGE)

re: fclean all

.PHONY: all clean fclean re run
