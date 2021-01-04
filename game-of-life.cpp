#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "draw.h"
#include "terminal.h"
#include "transition.h"

#define CLOCK_PER_CYCLE CLOCKS_PER_SEC / REFRESH_NSEC
#define REFRESH_SEC 0
#define REFRESH_NSEC 1000
#define Q 113

bool interrupted = false;
void sig_handler(int signo) {
    interrupted = true;
    (void)signo;
}

int main(int argc, char *argv[]) {
    if (argc < 6) {
        printf("usage: game-of-life <graphics-cell-width> <height> <width> <transitions> <period> [<fill>]\n");
        exit(1);
    }
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGINT\n");
        exit(1);
    }

    int graphics = atoi(argv[1]);
    int H = atoi(argv[2]), W = atoi(argv[3]);
    int T = atoi(argv[4]);
    int R = atoi(argv[5]);
    int O = argc == 7 ? atoi(argv[6]) : 10;

    time_t timer;
    srand((unsigned)time(&timer));

    bool field[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) field[i][j] = rand() % 100 < O;
    }

    bool *field_rows[H];
    for (int i = 0; i < H; i++) field_rows[i] = field[i];

    SDL_Renderer *renderer;
    SDL_Window *window;

    if (graphics) {
        init_draw(&renderer, &window, W, H, graphics);
        draw_matrix(renderer, field_rows, H, W, graphics);
    } else
        display(field_rows, H, W);

    struct timespec wait_time;
    wait_time.tv_sec = REFRESH_SEC;
    wait_time.tv_nsec = REFRESH_NSEC;

    SDL_Event event;
    int r = 0, t = 0;
    while (!interrupted) {
        nanosleep(&wait_time, NULL);
        if (SDL_PollEvent(&event) &&
            (event.type == SDL_QUIT ||
             (event.type == SDL_KEYDOWN &&
              event.key.keysym.sym == 'q'))) break;

        if (r++ < R * CLOCK_PER_CYCLE)
            continue;
        else
            r = 0;

        transition(field_rows, H, W);
        if (t++ >= T && T != -1) break;

        if (graphics) {
            draw_matrix(renderer, field_rows, H, W, graphics);
            continue;
        }

        clear(H);
        display(field_rows, H, W);
    }

    if (graphics) exit_draw(renderer, window);
    return 0;
}