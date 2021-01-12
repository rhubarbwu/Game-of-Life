
#include "graphics.h"

#include "colours.h"
#include "macros.h"

const unsigned COLOURS[5] = BLUE;

void init_draw(SDL_Renderer **renderer_ptr, SDL_Window **window_ptr, unsigned win_w, unsigned win_h, unsigned cell_size) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(win_w * cell_size, win_h * cell_size, 0, window_ptr, renderer_ptr);
    SDL_SetRenderDrawColor(*renderer_ptr,
                           COLOURS[0] >> 16 & 0xFF,
                           COLOURS[0] >> 4 & 0xFF,
                           COLOURS[0] & 0xFF, 255);
    SDL_RenderClear(*renderer_ptr);
    SDL_RenderPresent(*renderer_ptr);
}

void draw_matrix(SDL_Renderer *renderer, unsigned *field, unsigned H, unsigned W, unsigned cell_size) {
    SDL_Rect rect = {.x = 0, .y = 0, .w = (int)cell_size, .h = (int)cell_size};

    for (unsigned i = 0; i < H; i++) {
        for (unsigned j = 0; j < W; j++) {
            unsigned hex;
            if (field[i * W + j] <= 4)
                hex = COLOURS[field[i * W + j]];
            SDL_SetRenderDrawColor(renderer,
                                   hex >> 16 & 0xFF,
                                   hex >> 8 & 0xFF,
                                   hex & 0xFF,
                                   255);

            rect.x = j * cell_size;
            rect.y = i * cell_size;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}

void exit_draw(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
