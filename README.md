# Game of Life

An implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++ (or CUDA) for the terminal and the C graphics library.

### Configuration

There are five color stages for cells: alive, dead, and three dying stages in between. They're configured in `colours.h`.

## Building

Install the following dependencies:

- [g++](https://linux.die.net/man/1/g++) (CPU)
- [nvcc](https://developer.nvidia.com/cuda-toolkit) (CUDA)
- [sdl2](https://www.libsdl.org/)
- [sdl2-image](https://www.libsdl.org/projects/SDL_image/)

And run the desired Make rule.

```sh
make gol-cpu # g++
make gol-cuda # nvcc
```

## Usage

```sh
# CPU
gol-cpu <graphics-cell-width> <height> <width> <transitions> <period> [<fill>]

# CUDA: <graphics-cell-width> not implemented.
gol-cuda <graphics-cell-width> <height> <width> <transitions> <period> [<fill>]
```

Where:

- `graphic-cell-width` is a positive integer to indicate the width and height of each cell in SDL graphics.
  - Use `0` for terminal mode.
  - Not yet working in CUDA.
- `height` is the number of rows in the field.
- `width` is the number of columns in the field.
- `transitions` is the number of transitions/cycles/iterations of the Game of Life.
  - Use `-1` for infinite transitions.
- `period` is the approximate time between transitions.
  - `[1-100]` is recommended.
- `fill` is the percentage of the field that is filled at the start. This is a probabilistic randomized initiation.
  - Use a value between `[0-100]`.

### Quit

- In the terminal, issue `Ctrl-C` to interrupt and quit.
- If in graphics mode, pressing `q` or closing the window as normal (i.e. click red x) will also work.
