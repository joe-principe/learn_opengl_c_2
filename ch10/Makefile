# $@ - Target name
# $^ - Target dependencies

CC = gcc
CFLAGS = -Wall
LINKER_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl -lm

lookat: src/lookat.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

walk_around: src/walk_around.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

move_speed: src/move_speed.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

look_around: src/look_around.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

zoom: src/zoom.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

ex1: src/ex1.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o

ex2: src/ex2.c src/glad.c src/shader.c
	$(CC) $^ $(CFLAGS) $(LINKER_FLAGS) -o bin/$@.o
