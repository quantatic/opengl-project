CC = gcc.exe

OUT_FILENAME = opengl.exe

INCLUDE_FLAGS = -Iinclude
LDFLAGS = -Llib -lglfw3dll -lglew32 -lopengl32 -lm

BIN_DIR = bin
SRC_DIR = src

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OUT_FILE = $(BIN_DIR)/$(OUT_FILE)

all: $(SRC_FILES)
	/bin/bash -c "$(CC) $(SRC_FILES) $(INCLUDE_FLAGS) $(LDFLAGS) -o $(BIN_DIR)/opengl.exe"
