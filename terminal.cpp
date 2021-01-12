#include "terminal.h"

#include <iostream>

using namespace std;

void clear(int H) {
    for (int i = 0; i < H; i++)
        cout << "\e[2K\r\e[1A";
}

void display(int *field, int H, int W) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            cout << (field[i * W + j] == ALIVE ? "O" : " ");
        cout << "\n";
    }
}