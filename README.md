# Game of Life

An implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++ and CUDA for the terminal and SDL Graphics.

### Configuration

There are five color stages for cells: alive, dead, and three dying stages in between. They're configured in `colours.h`. By default, the CPU and CUDA versions have a (clever) colour difference.

## Building

Install the following dependencies:

- [g++](https://linux.die.net/man/1/g++) (CPU)
- [nvcc](https://developer.nvidia.com/cuda-toolkit) (CUDA)
- [sdl2](https://www.libsdl.org/)
- [sdl2-image](https://www.libsdl.org/projects/SDL_image/)

And run the desired Make rule.

```sh
make gol-cpu
make gol-cuda
```

## Usage

```sh
# CPU
gol-cpu <graphics-cell-size> <height> <width> <transitions> <period> [<fill>]

# CUDA
gol-cuda <graphics-cell-size> <height> <width> <transitions> <period> [<fill>]
```

Where:

- `graphic-cell-size` is a non-negative integer to indicate the width and height of each cell in SDL graphics.
  - Use `0` for terminal mode.
- `height` is the number of rows in the field.
- `width` is the number of columns in the field.
- `transitions` is the number of transitions/cycles/iterations of the Game of Life.
  - Use `-1` for infinite transitions.
- `period` is the number of seconds between transitions.
- `fill` is the percentage of the field that is filled at the start. This is a probabilistic randomized initiation.
  - Use a value between `[0-100]`.

### Quit

- In the terminal, issue `Ctrl-C` to interrupt and quit.
- If in graphics mode, pressing `q` or closing the window as normal (i.e. click red x) will also work.

## Acknowledgements

- [fsan/cuda_on_sdl](https://github.com/fsan/cuda_on_sdl) for guiding on SDL graphics and CUDA rendering.
