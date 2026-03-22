CC = gcc
CFLAGS = -g -Wall -Werror -Iinclude

AR = ar
ARFLAGS = rcs

SRC_DIR = src
BUILD = build
OUT = $(BUILD)/lib

SRCS = arena.c
SOURCES = $(foreach src,$(SRCS),$(SRC_DIR)/$(src))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD)/%.o)

TARGET = $(OUT)/liballocators.a

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS) | out
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(BUILD)/%.o: $(SRC_DIR)/%.c | build
	@echo "$@ -- $<"
	$(CC) -c $(CFLAGS) $< -o $@

# dirs

build:
	mkdir -p $(BUILD)

out:
	mkdir -p $(OUT)

# utilities

.PHONY: clean
clean:
	rm -rf $(BUILD) $(OUT)
#	rm -f compile_commands.json

.PHONY: clean-all
clean-all:
	rm -rf $(BUILD) $(OUT)
	rm -f compile_commands.json

.PHONY: ccjson
ccjson: clean
	@echo "Cleared build for bear"
	bear -- make all
