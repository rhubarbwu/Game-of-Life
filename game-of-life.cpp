#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <ctime>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("usage: game-of-life <height> <width> <transitions> [<odds>]\n");
        exit(1);
    }

    int H = atoi(argv[1]), W = atoi(argv[2]);
    int T = atoi(argv[3]);
    (void)T;
    int O = 12;
    if (argc == 5)
        O = atoi(argv[4]);

    time_t timer;
    srand((unsigned)time(&timer));

    bool board[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            board[i][j] = rand() % O == 0;
    }

    bool *board_rows[H];
    for (int i = 0; i < H; i++)
        board_rows[i] = board[i];
    (void)board_rows;

    return 0;
}