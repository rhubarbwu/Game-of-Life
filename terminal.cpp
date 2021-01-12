#include "terminal.h"

#include <iostream>

using namespace std;

void clear(unsigned H) {
    for (unsigned i = 0; i < H; i++)
        cout << "\e[2K\r\e[1A";
}

void display(unsigned *field, unsigned H, unsigned W) {
    for (unsigned i = 0; i < H; i++) {
        for (unsigned j = 0; j < W; j++)
            cout << (field[i * W + j] == ALIVE ? "O" : " ");
        cout << "\n";
    }
}