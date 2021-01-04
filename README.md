# Game of Life

An implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++ (or CUDA) for the terminal and the C graphics library.

## Building

Install the following dependencies:

- [sdl2](https://www.libsdl.org/)
- [sdl2-image](https://www.libsdl.org/projects/SDL_image/)

Run or copy the `cpu` Make rule to build the CPU program.

```sh
make cpu
```

## Usage

```sh
game-of-life-cpu <graphics-cell-width> <height> <width> <transitions> <period> [<fill>]
```

Where:

- `graphic-cell-width` is a positive integer to indicate the width and height of each cell in SDL graphics.
  - Use `0` for terminal mode.
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
