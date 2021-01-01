#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <ctime>

#include "terminal.h"

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("usage: game-of-life <height> <width> <transitions> <rate> [<odds>]\n");
        exit(1);
    }

    int H = atoi(argv[1]), W = atoi(argv[2]);
    int T = atoi(argv[3]);
    int R = atoi(argv[4]);
    int O = 10;
    if (argc == 6)
        O = atoi(argv[5]);

    time_t timer;
    srand((unsigned)time(&timer));

    bool field[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            field[i][j] = rand() % 100 < O;
    }

    bool *field_rows[H];
    for (int i = 0; i < H; i++)
        field_rows[i] = field[i];

    display(field_rows, H, W);
    for (int t = 0; t < T; t++) {
        sleep(R);
        clear(H);
        display(field_rows, H, W);
    }

    return 0;
}