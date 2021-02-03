#include <chrono>

#include "boilerplate.h"
#include "field.h"
#include "graphics.h"
#include "terminal.h"

using namespace std::chrono;

unsigned S, H, W, P, F;
int T;

SDL_WINDOW

int main(int argc, char *argv[]) {
    SANITY
    ARGUMENTS

    unsigned field[H * W];
    init_field(field, H, W, F);

    if (S) SDL_DRAW_INIT

    auto last_time = system_clock::now() - milliseconds(P);

    unsigned t = 0;
    while (!interrupted) {
        SDL_QUIT_EVENT_HANDLER

        auto now = system_clock::now();
        if (duration_cast<milliseconds>(now - last_time).count() >= P) {
            if (S) {
                SDL_DRAW_MATRIX
            } else {
                if (t > 0) clear(H);
                display(field, H, W);
            }

            transition(field, H, W);
            if (t++ >= T && T != -1)
                break;
            last_time = now;
        }
    }

    if (S) SDL_DRAW_EXIT

    return 0;
}
