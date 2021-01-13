#include <SDL2/SDL.h>

#include "boilerplate.h"
#include "field.h"
#include "graphics.h"
#include "macros.h"
#include "terminal.h"

unsigned S, H, W, P, F;
int T;

SDL_Renderer *renderer;
SDL_Window *window;

int main(int argc, char *argv[]) {
    SANITY;
    ARGUMENTS;

    unsigned field[H * W];
    initField(field, H, W, F);

    uint32_t time_step = P;
    uint32_t next_time_step = SDL_GetTicks();

    if (S) {
        init_draw(&renderer, &window, W, H, S);
        draw_matrix(renderer, field, H, W, S);
    } else
        display(field, H, W);

    unsigned t = 0;
    while (!interrupted) {
        SDL_Event event;
        if (SDL_PollEvent(&event) &&
            (event.type == SDL_QUIT ||
             (event.type == SDL_KEYDOWN &&
              event.key.keysym.sym == 'q'))) break;

        uint32_t now = SDL_GetTicks();
        if (next_time_step <= now) {
            if (S) {
                draw_matrix(renderer, field, H, W, S);
            } else {
                clear(H);
                display(field, H, W);
            }

            transition(field, H, W);
            if (t++ >= T && T != -1) break;
            next_time_step += time_step;
        }
    }

    if (S) exit_draw(renderer, window);
    return 0;
}
