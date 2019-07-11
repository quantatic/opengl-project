CC = gcc.exe

OUT_FILENAME = opengl.exe

INCLUDE_FLAGS = -Iinclude
LDFLAGS = -Llib -lglfw3dll -lglew32 -lopengl32 -lm

CFLAGS = -O3 -g -Wall

BIN_DIR = bin
SRC_DIR = src

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
HEADER_FILES = $(wildcard $(SRC_DIR)/*.h)

OUT_FILE = $(BIN_DIR)/$(OUT_FILE)

all: $(SRC_FILES) $(HEADER_FILES)
	/bin/bash -c "$(CC) $(SRC_FILES) $(INCLUDE_FLAGS) $(LDFLAGS) $(CFLAGS) -o $(BIN_DIR)/opengl.exe"
