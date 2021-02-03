NVCC = nvcc
FLAGS = -Wall -Wextra -Wshadow
DEPS = boilerplate.h colours.h rules.h terminal.o

.PHONY: all clean


gol-cpu: gol-cpu.o field.o graphics.o terminal.o
	$(CXX) ${FLAGS} -o gol-cpu $^ -lSDL2

gol-cpu-term: gol-cpu.to field.o terminal.o
	${CXX} ${FLAGS} -o gol-cpu-term $^ -DNO_SDL

gol-cuda: gol-cuda.o field-cuda.co graphics-cuda.co terminal.o
	${CXX} ${FLAGS} -o gol-cuda $^ -lSDL2 -lcudart

gol-cuda-term: gol-cuda.cto field-cuda.co terminal.o
	${CXX} ${FLAGS} -o gol-cuda-term $^ -lcudart -DNO_SDL


%.co: %.cu %.h
	${NVCC} -c $< -o $@ 

%.cto: %.cpp
	${NVCC} -c $< -o $@ -DNO_SDL

%.o: %.cpp %.h
	${CXX} -c $<

%.to: %.cpp
	${CXX} -c $< -o $@ -DNO_SDL


all: gol-cpu gol-cpu-term gol-cuda gol-cuda-term

clean:
	rm -rf gol-cpu gol-cpu-term gol-cuda gol-cuda-term *.co *.cto *.gch *.o *.to
