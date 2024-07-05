# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl

main: src/hello_triangle.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/hello_triangle.o

ex1: src/ex1.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/ex1.o

ex2: src/ex2.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/ex2.o

ex3: src/ex3.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/ex3.o
