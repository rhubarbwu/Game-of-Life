#ifndef BOILERPLATE_H
#define BOILERPLATE_H

#include <signal.h>

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

#define ARGUMENTS                         \
    S = atoi(argv[1]);                    \
    H = atoi(argv[2]), W = atoi(argv[3]); \
    T = atoi(argv[4]), P = atoi(argv[5]); \
    F = argc == 7 ? atoi(argv[6]) : 10;

bool interrupted = false;
void sig_handler(int signo) {
    interrupted = true;
    (void)signo;
    cout << "\n"
         << endl;
}

#endif
