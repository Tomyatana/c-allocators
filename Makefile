CC = gcc
INCLUDE_DIRS = include
CFLAGS = -g -Wall -Wextra -Werror $(foreach inc_dir,$(INCLUDE_DIRS),-I$(inc_dir))

AR = ar
ARFLAGS = rcs

SRC_DIR = src
BUILD = build
OUT = $(BUILD)/lib
TESTS = $(BUILD)/tests

SRCS = arena.c dyn_array.c
SOURCES = $(foreach src,$(SRCS),$(SRC_DIR)/$(src))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD)/%.o)

TARGET = $(OUT)/liballocators.a

.PHONY: all
all: $(TARGET) tests

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

tests_dir:
	mkdir -p $(TESTS)

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

# libs

UNITY_DIR = deps/Unity

.PHONY: unity
unity: $(BUILD)/unity.o

$(BUILD)/unity.o: $(UNITY_DIR)/src/unity.c build
	$(CC) -c $(CFLAGS) $< -o $@

# tests

TEST_CFLAGS = -g -Wall -Wextra -Og -Iinclude -I$(UNITY_DIR)/src
TEST_LDFLAGS = -L$(OUT)
TEST_LLIBS = -lallocators

.PHONY: tests
tests: arena_test dyn_array_test

arena_test: tests/arena_test.c $(TARGET) tests_dir unity
	$(CC) $(TEST_CFLAGS) $(BUILD)/unity.o $< $(TEST_LDFLAGS) $(TEST_LLIBS) -o $(TESTS)/$@
	$(TESTS)/$@

dyn_array_test: tests/dyn_array_test.c $(TARGET) tests_dir unity
	$(CC) $(TEST_CFLAGS) $(BUILD)/unity.o $< $(TEST_LDFLAGS) $(TEST_LLIBS) -o $(TESTS)/$@
	$(TESTS)/$@
