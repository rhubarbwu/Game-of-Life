# Game of Life

An implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++ (or CUDA) for the terminal and the C graphics library.

## Building

Run or copy the `cpu` Make rule to build the CPU program.

```sh
make cpu
```

## Usage

```sh
game-of-life-cpu <graphics> <height> <width> <transitions> <period> [<fill>]
```

Where:
- `graphics` is `0` for terminal and `1` for SDL graphics.
- `height` is the number of rows in the field.
- `width` is the number of columns in the field.
- `transitions` is the number of transitions/cycles/iterations of the Game of Life.
- `period` is the approximate time between transitions.
  - `[1-100]` is recommended.
- `fill` is the percentage of the field that is filled at the start. This is a probabilistic randomized initiation.
  - Use a value between `[0-100]`.

### Quit

Ctrl-C from terminal to quit. If in graphics mode, closing the window as normal (i.e. click red x) will also work.
