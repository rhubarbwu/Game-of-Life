#include <iostream>

#include "macros.h"

using namespace std;

void clear(int H) {
    up_to(i, H) cout << "\e[2K\r\e[1A";
}

void display(bool** field, int H, int W) {
    up_to(i, H) {
        up_to(j, W) {
            if (field[i][j])
                cout << "O";
            else
                cout << " ";
        }
        cout << "\n";
    }
}
