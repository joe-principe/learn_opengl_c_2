# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LDLIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl -lm

BIN_DIR = ./bin
SRC_DIR = ./src

# TODO: CHANGE THIS FOR EACH CHAPTER
MY_FILES = hello_triangle ex1 ex2 ex3

# SOURCES := $(foreach file, $(MY_FILES), $(SRC_DIR)/$(file).c)
# OUTPUTS := $(foreach file, $(MY_FILES), $(BIN_DIR)/$(file).o)

REQUIREMENTS = $(SRC_DIR)/glad.c

optimized: CFLAGS = -Wall -O3
RM = rm

# Unoptimized builds for all the files
.PHONY:all
.DELETE_ON_ERROR:
all: $(MY_FILES)

# -O3 optimized builds for all the files
.PHONY:optimized
optimized: $(MY_FILES)

# Unoptimized builds for a specific file in $(MY_FILES)
$(MY_FILES): $(REQUIREMENTS)
	$(CC) $^ $(SRC_DIR)/$@.c $(CFLAGS) $(LDLIBS) -o $(BIN_DIR)/$@.o

# Not sure why I did it this way looking back on it. Keeping it for future
# reference just in case
# $(MY_FILES): $(REQUIREMENTS) $(SOURCES)
# 	$(CC) $(REQUIREMENTS) $(filter $(SRC_DIR)/$@.c,$(SOURCES)) $(CFLAGS) \
# 		$(LDLIBS) -o $(filter $(BIN_DIR)/$@.o,$(OUTPUTS))

# Removes all of the binaries in ./bin
.PHONY: clean
clean:
	$(RM) $(BIN_DIR)/*
