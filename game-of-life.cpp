#include <signal.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "boilerplate.h"
#include "graphics.h"
#include "macros.h"
#include "terminal.h"
#include "transition.h"

int main(int argc, char *argv[]) {
    SANITY;
    ARGUMENTS;

    time_t timer;
    srand((unsigned)time(&timer));

    int field[H][W];
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            field[i][j] = rand() % 100 < O ? ALIVE : 0;

    int *field_rows[H];
    for (int i = 0; i < H; i++) field_rows[i] = field[i];

    SDL_Renderer *renderer;
    SDL_Window *window;

    if (graphics) {
        init_draw(&renderer, &window, W, H, graphics);
        draw_matrix(renderer, field_rows, H, W, graphics);
    } else
        display(field_rows, H, W);

    struct timespec wait_time = {.tv_sec = REFRESH_S, .tv_nsec = REFRESH_NS};
    int r = 0, t = 0;
    while (!interrupted) {
        SDL_Event event;
        if (SDL_PollEvent(&event) &&
            (event.type == SDL_QUIT ||
             (event.type == SDL_KEYDOWN &&
              event.key.keysym.sym == 'q'))) break;

        nanosleep(&wait_time, NULL);
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
