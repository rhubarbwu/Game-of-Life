#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#include "colours.h"
#include "macros.h"

void init_draw(SDL_Renderer **renderer, SDL_Window **window, unsigned win_w, unsigned win_h, unsigned cell_size);
void draw_matrix(SDL_Renderer *renderer, unsigned *field, unsigned H, unsigned W, unsigned cell_size);
void exit_draw(SDL_Renderer *renderer, SDL_Window *window);

#endif
