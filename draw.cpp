#include <SDL2/SDL.h>

#define BLACK 0, 0, 0
#define ORANGE 0xFB, 0x7E, 0x14

void init_draw(SDL_Renderer **renderer_ptr, SDL_Window **window_ptr, int win_w, int win_h, int cell_size) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(win_w * cell_size, win_h * cell_size, 0, window_ptr, renderer_ptr);
    SDL_SetRenderDrawColor(*renderer_ptr, BLACK, 0);
    SDL_RenderClear(*renderer_ptr);
    SDL_RenderPresent(*renderer_ptr);
}

void draw_matrix(SDL_Renderer *renderer, bool **field, int H, int W, int cell_size) {
    SDL_Rect rect = {.x = 0, .y = 0, .w = cell_size, .h = cell_size};

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (field[i][j])
                SDL_SetRenderDrawColor(renderer, ORANGE, 255);
            else
                SDL_SetRenderDrawColor(renderer, BLACK, 0);

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