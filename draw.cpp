#include <SDL2/SDL.h>

#define BLACK 0, 0, 0
#define ORANGE 0xFB, 0x7E, 0x14

void init_draw(SDL_Renderer **renderer_ptr, SDL_Window **window_ptr, int win_w, int win_h) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(win_w, win_h, 0, window_ptr, renderer_ptr);
    SDL_SetRenderDrawColor(*renderer_ptr, BLACK, 0);
    SDL_RenderClear(*renderer_ptr);
    SDL_RenderPresent(*renderer_ptr);
}

void draw_matrix(SDL_Renderer *renderer, bool **field, int H, int W) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (field[i][j])
                SDL_SetRenderDrawColor(renderer, ORANGE, 255);
            else
                SDL_SetRenderDrawColor(renderer, BLACK, 0);
            SDL_RenderDrawPoint(renderer, j, i);
        }
    }
    SDL_RenderPresent(renderer);
}

void exit_draw(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}