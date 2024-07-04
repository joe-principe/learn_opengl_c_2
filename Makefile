# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl

release: hello_window.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o hello_window
