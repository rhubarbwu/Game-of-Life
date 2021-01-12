#include <signal.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <SDL2/SDL.h>

#include "boilerplate.h"
#include "field.h"
#include "graphics.h"
#include "macros.h"
#include "terminal.h"

int main(int argc, char *argv[]) {
    SANITY;
    ARGUMENTS;

    time_t timer;
    srand((unsigned)time(&timer));

    int field[H * W];

    for (int i = 0; i < H * W; i++)
        field[i] = rand() % 100 < O ? ALIVE : 0;

    SDL_Renderer *renderer;
    SDL_Window *window;

    if (graphics) {
        init_draw(&renderer, &window, W, H, graphics);
        draw_matrix(renderer, field, H, W, graphics);
    } else
        display(field, H, W);

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

        transition(field, H, W);
        if (t++ >= T && T != -1) break;

        if (graphics) {
            draw_matrix(renderer, field, H, W, graphics);
            continue;
        }
        clear(H);
        display(field, H, W);
    }

    if (graphics) exit_draw(renderer, window);
    return 0;
}
