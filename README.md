# Game of Life

An implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++ and CUDA for the terminal and SDL Graphics.

### Configuration

Some things are easy to configure.

#### Colours

There are five color stages for cells: alive, dead, and three dying stages in between. They're configured in `colours.h`. By default, the CPU and CUDA versions have some clever colours.

#### Rules

Additionally, by default the original rules from [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) are used, and they're configured in `rules.h`, which is used by all versions.

## Building

Install the following dependencies:

- [g++](https://linux.die.net/man/1/g++)
  - [clang++](https://clang.llvm.org/) was previous (erroneously) used.
- [nvcc](https://developer.nvidia.com/cuda-toolkit) (CUDA only)
- [sdl2](https://www.libsdl.org/) and [sdl2-image](https://www.libsdl.org/projects/SDL_image/) (optional)

And run Make rule for the desired version.

```sh
make gol-cpu
make gol-cuda

# If you do not have sdl2/sdl2-image
make gol-cpu-term
make gol-cuda-term
```

## Usage

```sh
gol-<version> <graphics-cell-size> <height> <width> <transitions> <period> [<fill>]
```

Where:

- `graphic-cell-size` is a non-negative integer to indicate the width and height of each cell in SDL graphics.
  - Use `0` for terminal mode. (Required for `*-term` versions.)
- `height` is the number of rows in the field.
- `width` is the number of columns in the field.
- `transitions` is the number of transitions/cycles/iterations of the Game of Life.
  - Use `-1` for infinite transitions.
- `period` is the number of milliseconds between transitions.
- `fill` is the percentage of the field that is filled at the start. This is a probabilistic randomized initiation.
  - Use a value between `[0-100]`.

### Quit

- In the terminal, issue `Ctrl-C` to interrupt and quit.
- If in graphics mode, pressing `q` or closing the window as normal (i.e. click red x) will also work.

## Acknowledgements

- [fsan/cuda_on_sdl](https://github.com/fsan/cuda_on_sdl) for guidance on SDL graphics and CUDA rendering.
