
#include "graphics.h"

#include "colours.h"
#include "macros.h"

void init_draw(SDL_Renderer **renderer_ptr, SDL_Window **window_ptr, int win_w, int win_h, int cell_size) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(win_w * cell_size, win_h * cell_size, 0, window_ptr, renderer_ptr);
    SDL_SetRenderDrawColor(*renderer_ptr,
                           COLOUR_0 >> 16 & 0xFF,
                           COLOUR_0 >> 4 & 0xFF,
                           COLOUR_0 & 0xFF, 255);
    SDL_RenderClear(*renderer_ptr);
    SDL_RenderPresent(*renderer_ptr);
}

void draw_matrix(SDL_Renderer *renderer, int *field, int H, int W, int cell_size) {
    SDL_Rect rect = {.x = 0, .y = 0, .w = cell_size, .h = cell_size};

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int hex;
            switch (field[i * W + j]) {
                case 0:
                    hex = COLOUR_0;
                    break;
                case 1:
                    hex = COLOUR_1;
                    break;
                case 2:
                    hex = COLOUR_2;
                    break;
                case 3:
                    hex = COLOUR_3;
                    break;
                case 4:
                    hex = COLOUR_4;
                    break;
            }
            SDL_SetRenderDrawColor(renderer,
                                   hex >> 16 & 0xFF,
                                   hex >> 4 & 0xFF,
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
