# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LINKER_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl -lm

ambient: src/ambient.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

diffuse: src/diffuse.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

specular: src/specular.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

ex1: src/ex1.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

ex2: src/ex2.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

ex3: src/ex3.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

ex4: src/ex4.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o
