CC = g++.exe

SHELL_CMD = cmd.exe /c
#SHELL_CMD = /bin/sh -c

SRC_EXTENSION = cpp
HEADER_EXTENSION = hpp

OUT_FILENAME = opengl.exe

CFLAGS = -O3 -g -Wall -Iinclude
LDFLAGS = -Llib -lglfw3dll -lglew32 -lopengl32 -lm

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.$(SRC_EXTENSION))
HEADER_FILES = $(wildcard $(SRC_DIR)/*.$(HEADER_EXTENSION))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.$(SRC_EXTENSION),$(BUILD_DIR)/%.o,$(SRC_FILES))

OUT_FILE = $(BIN_DIR)/$(OUT_FILENAME)

$(OUT_FILE): $(OBJ_FILES)
	$(SHELL_CMD) "$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(OUT_FILE)"

run: $(OUT_FILE)
	bin/$(OUT_FILENAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXTENSION) $(HEADER_FILES)
	$(SHELL_CMD) "$(CC) -c $< $(CFLAGS) -o $@"

clean:
	rm -f $(OBJ_FILES)
	rm -f $(OUT_FILE)
