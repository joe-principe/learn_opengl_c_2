# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LINKER_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl -lm

main: src/main.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o
