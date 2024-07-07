# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl -lm

ins_outs: src/ins_outs.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/$@.o

uniforms: src/uniforms.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/$@.o

more_attributes: src/more_attributes.c glad.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/$@.o

rff: src/rff.c glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/$@.o

ex1: src/ex1.c glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/$@.o

ex2: src/ex2.c glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/$@.o

ex3: src/ex3.c glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o bin/$@.o
