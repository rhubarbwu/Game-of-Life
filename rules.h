#define NEIGHBOURS                                                                \
    neighbours += (j > 0 && prev_field[index - 1] == ALIVE);                      \
    neighbours += (j < W - 1 && prev_field[index + 1] == ALIVE);                  \
    neighbours += (i > 0 && prev_field[index - W] == ALIVE);                      \
    neighbours += (i < H - 1 && prev_field[index + W] == ALIVE);                  \
                                                                                  \
    neighbours += (j > 0 && i > 0 && prev_field[index - W - 1] == ALIVE);         \
    neighbours += (j > 0 && i < H - 1 && prev_field[index + W - 1] == ALIVE);     \
    neighbours += (j < W - 1 && i < H - 1 && prev_field[index + W + 1] == ALIVE); \
    neighbours += (j < W - 1 && i > 0 && prev_field[index - W + 1] == ALIVE);

#define RULE                  \
    if (neighbours / 2 == 1)  \
        field[index] = ALIVE; \
    else                      \
        field[index] = prev_field[index] == 0 ? 0 : prev_field[index] - 1;
