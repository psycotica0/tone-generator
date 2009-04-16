.PHONY: clean bundle

generator: generator.c
	$(CC) -o generator `sdl-config --cflags --libs` generator.c

bundle: 
	sh makeAppBundle

clean: 
	$(RM) generator

