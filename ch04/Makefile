# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl

release: src/hello_window.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/hello_window.o
