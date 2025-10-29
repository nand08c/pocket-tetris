# Directories
SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build

# Compiler and flags
CC = avr-gcc
UC = atmega328p
CFLAGS = -I/usr/avr/include/ -I$(INC_DIR) -Wall -mmcu=$(UC) -DF_CPU=16000000U -O0

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

# Upload Rule
upload:
	@for port in $$(ls /dev/ttyUSB* 2>/dev/null); do \
		echo "Attempting to upload using port: $$port"; \
		if sudo avrdude -c arduino -P $$port -p $(UC) -b 57600 -v -Uflash:w:$(BUILD_DIR)/$(TARGET):e; then \
			echo "Upload successful on port $$port"; \
			break; \
		fi; \
	done

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
