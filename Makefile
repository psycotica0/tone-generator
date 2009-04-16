.PHONY: clean

generator: generator.c
	g++ -o generator `sdl-config --cflags --libs` generator.c

clean: 
	rm -f generator generator.o

