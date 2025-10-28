# Directories
SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build

# Compiler and flags
CC = avr-gcc
UC = atmega328p
CFLAGS = -I/usr/avr/include/ -I$(INC_DIR) -Wall -mmcu=$(UC) -DF_CPU=16000000F

# Target
TARGET = pocket_tetris

# Source files and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Rule to link object files into the final executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile C source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
