CXX = g++
FLAGS = -Wall -Wextra -Wshadow

.PHONY: clean

gol-cpu: gol-cpu.o field.o graphics.o terminal.o | *.h
	${CXX} ${FLAGS} $^ -o gol-cpu -lSDL2

gol-cuda: gol-cuda.o field-cuda.co graphics-cuda.co terminal.o
	${CXX} ${FLAGS} -o gol-cuda $^ -lSDL2 -lcudart

gol-cuda.o: gol-cuda.cpp boilerplate.h macros.h terminal.h
	${CXX} -c -o gol-cuda.o gol-cuda.cpp

%.co: %.cu %.h
	nvcc -c $< -o $@

%.o: %.cpp %.h
	${CXX} -c $< -o $@

clean:
	rm -rf gol-cpu gol-cuda *.co *.o
