CC = g++
CFLAGS = -Wall -Wextra -Wshadow
SDL_FLAGS = 

gol-cuda: game-of-life.cu terminal.o | *.h
	nvcc $^ -o gol-cuda

gol-cpu: game-of-life.o graphics.o terminal.o transition.o | *.h
	${CC} ${CFLAGS} $^ -o gol-cpu `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lm

%.o: %.cpp
	${CC} ${CFLAGS} -c $^

clean:
	rm -rf gol-cpu gol-cuda *.o
