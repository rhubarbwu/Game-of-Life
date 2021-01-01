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

void clear(int H) {
    for (int i = 0; i < H; i++)
        cout << "\e[2K\r\e[1A";
}

void display(bool **board, int H, int W) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            cout << board[i][j];
        cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("usage: game-of-life <height> <width> <transitions> <rate> [<odds>]\n");
        exit(1);
    }

    int H = atoi(argv[1]), W = atoi(argv[2]);
    int T = atoi(argv[3]);
    int R = atoi(argv[4]);
    int O = 12;
    if (argc == 6)
        O = atoi(argv[5]);

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

    display(board_rows, H, W);
    for (int t = 0; t < T; t++) {
        sleep(R);
        clear(H);
        display(board_rows, H, W);
    }

    return 0;
}