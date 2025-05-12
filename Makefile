CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR := src
BUILD_DIR := build
EXEC = $(BUILD_DIR)/shell

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

all: $(EXEC)

$(EXEC): | $(BUILD_DIR) $(OBJ)
	$(CC) $(OBJ) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
