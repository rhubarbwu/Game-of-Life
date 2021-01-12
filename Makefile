CXX = g++
FLAGS = -Wall -Wextra -Wshadow

gol-cpu: gol-cpu.o field.o graphics.o terminal.o | *.h
	${CXX} ${FLAGS} $^ -o gol-cpu -lSDL2 -lcudart

gol-cuda: gol-cuda.o field_cuda.o terminal.o | *.h
	${CXX} ${FLAGS} -o gol-cuda $^ -lSDL2 -lcudart

%.o: %.cpp
	${CXX} -c $< -o $@

clean:
	rm -rf gol-cpu gol-cuda *.o
