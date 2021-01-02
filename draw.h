#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

void init_draw(SDL_Renderer **renderer, SDL_Window **window, int win_w, int win_h);
void draw_matrix(SDL_Renderer *renderer, bool ** field, int H, int W);
void exit_draw(SDL_Renderer *renderer, SDL_Window *window);

#endif