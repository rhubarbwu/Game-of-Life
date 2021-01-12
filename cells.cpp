#include "macros.h"

void transition(int **field, int H, int W) {
    int prev_field[H][W];
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            prev_field[i][j] = field[i][j];

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            bool left = (j > 0 && prev_field[i][j - 1] == ALIVE);
            bool right = (j < W - 1 && prev_field[i][j + 1] == ALIVE);
            bool above = (i > 0 && prev_field[i - 1][j] == ALIVE);
            bool below = (i < H - 1 && prev_field[i + 1][j] == ALIVE);

            int neighbours = left + right + above + below;
            if (neighbours / 2 == 1) {
                field[i][j] = ALIVE;
                continue;
            }

            field[i][j] = prev_field[i][j] == 0 ? 0 : prev_field[i][j] - 1;
        }
    }
}