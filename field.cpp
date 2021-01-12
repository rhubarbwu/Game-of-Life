#include "field.h"

void initField(unsigned *field, unsigned H, unsigned W, unsigned fill) {
    time_t timer;
    srand((unsigned)time(&timer));

    for (unsigned i = 0; i < H * W; i++)
        field[i] = rand() % 100 < fill ? ALIVE : 0;
}

void transition(unsigned *field, unsigned H, unsigned W) {
    unsigned prev_field[H][W];
    for (unsigned i = 0; i < H; i++)
        for (unsigned j = 0; j < W; j++)
            prev_field[i][j] = field[i * W + j];

    for (unsigned i = 0; i < H; i++) {
        for (unsigned j = 0; j < W; j++) {
            bool left = (j > 0 && prev_field[i][j - 1] == ALIVE);
            bool right = (j < W - 1 && prev_field[i][j + 1] == ALIVE);
            bool above = (i > 0 && prev_field[i - 1][j] == ALIVE);
            bool below = (i < H - 1 && prev_field[i + 1][j] == ALIVE);

            unsigned neighbours = left + right + above + below;
            if (neighbours / 2 == 1) {
                field[i * W + j] = ALIVE;
                continue;
            }

            field[i * W + j] = prev_field[i][j] == 0 ? 0 : prev_field[i][j] - 1;
        }
    }
}