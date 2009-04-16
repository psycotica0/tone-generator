.PHONY: clean

generator: generator.c
	$(CC) -o generator `sdl-config --cflags --libs` generator.c

clean: 
	$(RM) generator

