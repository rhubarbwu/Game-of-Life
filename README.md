# Game of Life

An implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++ (or CUDA) for the terminal and the C graphics library.

## Building

Run or copy the `cpp` Make rule to build the CPU program.

```sh
make cpu
```

## Usage

```sh
game-of-life-cpu <height> <width> <transitions> <rate> <fill>
```

Where:

- `height` is the number of rows in the field.
- `width` is the number of columns in the field.
- `transitions` is the number of transitions/cycles/iterations of the Game of Life.
- `rate` is the approximate refresh rate between transitions.
  - Behaviour is untested on Microsoft Windows.
- `fill` is the percentage of the field that is filled at the start. This is a probabilistic randomized initiation.
  - Use a value between `[0-100]`.
