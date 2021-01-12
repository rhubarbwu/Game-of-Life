CXX = g++
FLAGS = -Wall -Wextra -Wshadow

.PHONY: clean

gol-cpu: gol-cpu.o field.o graphics.o terminal.o | *.h
	${CXX} ${FLAGS} $^ -o gol-cpu -lSDL2 -lcudart

gol-cuda: gol-cuda.o field_cuda.co graphics_cuda.co terminal.o
	${CXX} ${FLAGS} -o gol-cuda $^ -lSDL2 -lcudart

gol-cuda.o: gol-cuda.cpp boilerplate.h macros.h terminal.h
	${CXX} -c -o gol-cuda.o gol-cuda.cpp

%.co: %.cu
	nvcc -c $< -o $@

%.o: %.cpp
	${CXX} -c $< -o $@

clean:
	rm -rf gol-cpu gol-cuda *.co *.o
