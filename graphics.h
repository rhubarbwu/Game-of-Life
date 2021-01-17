#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifndef NO_SDL
#include <SDL2/SDL.h>

#include "colours.h"

void init_draw(SDL_Renderer **renderer, SDL_Window **window, unsigned win_w, unsigned win_h, unsigned cell_size);
void draw_matrix(SDL_Renderer *renderer, unsigned *field, unsigned H, unsigned W, unsigned cell_size);
void exit_draw(SDL_Renderer *renderer, SDL_Window *window);

#define SDL_DRAW_EXIT exit_draw(renderer, window);
#define SDL_DRAW_INIT \
    init_draw(&renderer, &window, W, H, S);
#define SDL_DRAW_MATRIX draw_matrix(renderer, field, H, W, S);
#define SDL_QUIT_EVENT_HANDLER           \
    SDL_Event event;                     \
    if (SDL_PollEvent(&event) &&         \
        (event.type == SDL_QUIT ||       \
         (event.type == SDL_KEYDOWN &&   \
          event.key.keysym.sym == 'q'))) \
        break;
#define SDL_WINDOW          \
    SDL_Renderer *renderer; \
    SDL_Window *window;

#else
#define SDL_DRAW_EXIT ;
#define SDL_DRAW_INIT ;
#define SDL_DRAW_MATRIX ;
#define SDL_QUIT_EVENT_HANDLER ;
#define SDL_WINDOW ;

#endif

#endif
