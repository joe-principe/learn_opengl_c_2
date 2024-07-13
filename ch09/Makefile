# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LINKER_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl -lm

going3d: src/going3d.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

more3d: src/more3d.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

zbuf: src/zbuf.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

cubes: src/cubes.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

ex1: src/ex1.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

ex2: src/ex2.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

ex3: src/ex3.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o
