#include "field.h"

void init_field(unsigned *field, unsigned H, unsigned W, unsigned fill) {
    time_t timer;
    srand((unsigned)time(&timer));

    for (unsigned i = 0; i < H * W; i++)
        field[i] = rand() % 100 < fill ? ALIVE : 0;
}

void transition(unsigned *field, unsigned H, unsigned W) {
    unsigned prev_field[H * W];
    for (unsigned i = 0; i < H * W; i++) prev_field[i] = field[i];

    for (unsigned index = 0; index < H * W; index++) {
        unsigned i = index / W;
        unsigned j = index % W;

        unsigned neighbours = 0;
        NEIGHBOURS
        RULE
    }
}