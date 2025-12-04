ASM=nasm

SRC_DIR=src
BUILD_DIR=build

$(BUILD_DIR)/main.img: $(BUILD_DIR)/main.bin
	cp $(BUILD_DIR)/main.bin $(BUILD_DIR)/main_truncated.img
	truncate -s 1440k $(BUILD_DIR)/main_truncated.img

$(BUILD_DIR)/main.bin: $(SRC_DIR)/init.asm
	$(ASM) $(SRC_DIR)/init.asm -f bin -o $(BUILD_DIR)/main.bin