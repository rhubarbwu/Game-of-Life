CXX = g++
FLAGS = -Wall -Wextra -Wshadow
DEPS = boilerplate.h colours.h rules.h terminal.o

.PHONY: all clean

gol-cpu: gol-cpu.o field.o graphics.o ${DEPS}
	${CXX} ${FLAGS} -o gol-cpu $^ -lSDL2 

gol-cpu-term: gol-cpu.to field.o ${DEPS}
	${CXX} ${FLAGS} -o gol-cpu-term $^ -DNO_SDL

gol-cuda: gol-cuda.o field-cuda.co graphics-cuda.co ${DEPS}
	${CXX} ${FLAGS} -o gol-cuda $^ -lSDL2 -lcudart

gol-cuda-term: gol-cuda.cto field-cuda.co ${DEPS}
	${CXX} ${FLAGS} -o gol-cuda-term $^ -lcudart -DNO_SDL


%.co: %.cu %.h
	nvcc -c $< -o $@ 

gol-cuda.cto: gol-cuda.cpp
	nvcc -c $< -o $@ -DNO_SDL

%.to: %.cpp
	${CXX} -c $< -o $@ -DNO_SDL

%.o: %.cpp %.h
	${CXX} -c $< -o $@

all: gol-cpu gol-cpu-term gol-cuda gol-cuda-term

clean:
	rm -rf gol-cpu gol-cpu-term gol-cuda gol-cuda-term *.co *.cto *.o *.to
