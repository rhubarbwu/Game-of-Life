#include <SDL2/SDL.h>

#include <chrono>
#include <ctime>

#include "boilerplate.h"
#include "colours.h"
#include "field-cuda.h"
#include "graphics-cuda.h"
#include "macros.h"
#include "terminal.h"

using namespace std::chrono;

unsigned S, H, W, F, P;
int T;

SDL_WINDOW

int main(int argc, char* argv[]) {
    SANITY
    ARGUMENTS

    SDL_CHECK_INIT

    uint32_t time_step = P;
    uint32_t next_time_step = SDL_GetTicks();

    if (S) {
        SDL_BOILERPLATE
    }

    unsigned field[H * W];
    initField(field, H, W, F);

    auto last_time = system_clock::now() - milliseconds(P);

    unsigned t = 0;
    while (!interrupted) {
        SDL_QUIT_EVENT_HANDLER

        auto now = system_clock::now();
        if (duration_cast<milliseconds>(now - last_time).count() >= P) {
            if (S) {
                SDL_DRAW
            } else {
                clear(H);
                display(field, H, W);
            }

            transition(field, H, W);
            if (t++ >= T && T != -1) break;
            last_time = now;
        }
    }

    if (S) SDL_DESTROY_QUIT

    return 0;
}
