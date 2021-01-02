cpu:
	g++ -Wall -Wextra -Wshadow -o game-of-life-cpu game-of-life.cpp draw.cpp `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lm

clean:
	rm game-of-life-cpu game-of-life-cpu.o draw.o