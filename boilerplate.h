#ifndef BOILERPLATE_H
#define BOILERPLATE_H

#include <iostream>

using namespace std;

#define SANITY                                                                                                        \
    if (argc < 6) {                                                                                                   \
        cout << "usage: game-of-life <graphics-cell-width> <height> <width> <transitions> <period> [<fill>]" << endl; \
        exit(1);                                                                                                      \
    }                                                                                                                 \
    if (signal(SIGINT, sig_handler) == SIG_ERR) {                                                                     \
        cout << "\ncan't catch SIGINT" << endl;                                                                       \
        exit(1);                                                                                                      \
    }

#define ARGUMENTS                             \
    int graphics = atoi(argv[1]);             \
    int H = atoi(argv[2]), W = atoi(argv[3]); \
    int T = atoi(argv[4]);                    \
    int R = atoi(argv[5]);                    \
    int O = argc == 7 ? atoi(argv[6]) : 10;

bool interrupted = false;
void sig_handler(int signo) {
    interrupted = true;
    (void)signo;
}

#endif
