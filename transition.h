#include "macros.h"

void transition(bool **field, int H, int W) {
    bool prev_field[H][W];
    up_to(i, H) {
        up_to(j, W) prev_field[i][j] = field[i][j];
    }

    up_to(i, H) {
        up_to(j, W) {
            bool left = (j > 0 && prev_field[i][j - 1]);
            bool right = (j < W - 1 && prev_field[i][j + 1]);
            bool above = (i > 0 && prev_field[i - 1][j]);
            bool below = (i < H - 1 && prev_field[i + 1][j]);

            int sum = left + right + above + below;
            field[i][j] = sum / 2 == 1;
        }
    }
}