# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl

chapter: src/main.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/$@.o
