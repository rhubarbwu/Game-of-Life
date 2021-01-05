gol-cpu: game-of-life.cpp
	g++ -Wall -Wextra -Wshadow -o gol-cpu game-of-life.cpp graphics.cpp `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lm

clean:
	rm gol-cpu
