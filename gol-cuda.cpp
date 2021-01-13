
#include <SDL2/SDL.h>

#include "boilerplate.h"
#include "colours.h"
#include "field_cuda.h"
#include "graphics_cuda.h"
#include "macros.h"
#include "terminal.h"

using namespace std;

unsigned S, H, W, F, P;
int T;

SDL_Renderer* renderer;
SDL_Surface* screen;
SDL_Texture* texture;
SDL_Window* window;

uint32_t* graphics_buffer;

int main(int argc, char* argv[]) {
    SANITY;
    ARGUMENTS;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cerr << "could not initialize sdl2: " << SDL_GetError() << endl;
        return 1;
    }

    uint32_t time_step = P;
    uint32_t next_time_step = SDL_GetTicks();

    if (S) {
        window = SDL_CreateWindow(
            "main",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            W * S, H * S,
            SDL_WINDOW_SHOWN);
        if (window == NULL) {
            cerr << "could not create window: "
                 << SDL_GetError()
                 << "Reverting to terminal."
                 << endl;
            S = 0;
        }
        screen = SDL_CreateRGBSurface(0, W * S, H * S, 32,
                                      R_MASK,
                                      G_MASK,
                                      B_MASK,
                                      A_MASK);
        if (screen == NULL) {
            SDL_Log("SDL_CreateRGBSurface() failed: %s.", SDL_GetError());
            S = 0;
        }
        renderer = SDL_CreateRenderer(window, -1,
                                      SDL_RENDERER_ACCELERATED |
                                          SDL_RENDERER_PRESENTVSYNC);
        texture = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING |
                                        SDL_TEXTUREACCESS_TARGET,
                                    W * S, H * S);
        graphics_buffer = gpuAlloc(H * W * S * S);
        if (graphics_buffer == NULL) {
            cerr << "failed to alloc gpu memory; reverting to terminal" << endl;
            S = 0;
        }
    }

    unsigned field[H * W];
    initField(field, H, W, F);
    if (!S) display(field, H, W);

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
                SDL_LockSurface(screen);
                render(screen, graphics_buffer, field, S, H, W);
                SDL_UnlockSurface(screen);
                SDL_UpdateTexture(texture, NULL,
                                  screen->pixels,
                                  screen->pitch);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
            } else {
                clear(H);
                display(field, H, W);
            }

            transition(field, H, W);
            if (t++ >= T && T != -1) break;
            next_time_step += time_step;
        }
    }

    if (S) {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    };

    SDL_Quit();

    return 0;
}
