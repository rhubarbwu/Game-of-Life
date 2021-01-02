void transition(bool **field, int H, int W) {
    bool prev_field[H][W];
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            prev_field[i][j] = field[i][j];

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            bool left = (j > 0 && prev_field[i][j - 1]);
            bool right = (j < W - 1 && prev_field[i][j + 1]);
            bool above = (i > 0 && prev_field[i - 1][j]);
            bool below = (i < H - 1 && prev_field[i + 1][j]);

            int sum = left + right + above + below;
            field[i][j] = sum / 2 == 1;
        }
    }
}