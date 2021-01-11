PROGRAM_NAME := gfx3d
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
DEBUG ?= 0

CC := gcc
CSTD := -std=c11
INC_FLAGS := -I$(INC_DIR) $(shell pkg-config --cflags sdl2)
LDFLAGS	:= -lm $(shell pkg-config --libs sdl2)
CFLAGS := -Wall -Wextra -pedantic $(INC_FLAGS) -MMD -MP
CFLAGS_DEBUG := -g -DDEBUG
CFLAGS_RELEASE := -O2

ifeq ($(DEBUG), 1)
	CFLAGS += $(CFLAGS_DEBUG)
	TARGET_DIR := $(BUILD_DIR)/debug
else
	CFLAGS += $(CFLAGS_RELEASE)
	TARGET_DIR := $(BUILD_DIR)/release
endif

TARGET := $(TARGET_DIR)/$(PROGRAM_NAME)
SRCS := $(shell find $(SRC_DIR) -name *.c -or -name *.cpp)
OBJ_DIR := $(TARGET_DIR)/obj
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
$(info $(TARGET))

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Include the .d makefiles. The '-' at the front suppresses errors of missing Makefiles.
# Initially, all the .d files will be missing and we don't want those errors to show up.
-include $(DEPS)
