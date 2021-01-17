#ifndef GRAPHICS_CUDA_H
#define GRAPHICS_CUDA_H

#pragma once

#ifndef NO_SDL
#include <SDL2/SDL.h>
#include <stdint.h>

#include "colours.h"

__device__ const unsigned COLOURS[5] = GREEN;

uint32_t* gpuAlloc(unsigned screen_size);
void gpuFree(void* gpu_mem);
unsigned gpuBlit(void* src, void* dst, unsigned screen_size);
int render(SDL_Surface* screen,
           void* cuda_pixels,
           unsigned* field, unsigned S, unsigned H, unsigned W);

#define SDL_BOILERPLATE                                                      \
    window = SDL_CreateWindow(                                               \
        "main",                                                              \
        SDL_WINDOWPOS_UNDEFINED,                                             \
        SDL_WINDOWPOS_UNDEFINED,                                             \
        W * S, H * S,                                                        \
        SDL_WINDOW_SHOWN);                                                   \
    if (window == NULL) {                                                    \
        cerr << "could not create window: "                                  \
             << SDL_GetError()                                               \
             << "Reverting to terminal."                                     \
             << endl;                                                        \
        S = 0;                                                               \
    }                                                                        \
    screen = SDL_CreateRGBSurface(0, W * S, H * S, 32,                       \
                                  R_MASK,                                    \
                                  G_MASK,                                    \
                                  B_MASK,                                    \
                                  A_MASK);                                   \
    if (screen == NULL) {                                                    \
        SDL_Log("SDL_CreateRGBSurface() failed: %s.", SDL_GetError());       \
        S = 0;                                                               \
    }                                                                        \
    renderer = SDL_CreateRenderer(window, -1,                                \
                                  SDL_RENDERER_ACCELERATED |                 \
                                      SDL_RENDERER_PRESENTVSYNC);            \
    texture = SDL_CreateTexture(renderer,                                    \
                                SDL_PIXELFORMAT_ARGB8888,                    \
                                SDL_TEXTUREACCESS_STREAMING |                \
                                    SDL_TEXTUREACCESS_TARGET,                \
                                W * S, H * S);                               \
    graphics_buffer = gpuAlloc(H * W * S * S);                               \
    if (graphics_buffer == NULL) {                                           \
        cerr << "failed to alloc gpu memory; reverting to terminal" << endl; \
        S = 0;                                                               \
    }

#define SDL_CHECK_INIT                                                   \
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {                             \
        cerr << "could not initialize sdl2: " << SDL_GetError() << endl; \
        return 1;                                                        \
    }

#define SDL_DESTROY_QUIT           \
    SDL_DestroyTexture(texture);   \
    SDL_DestroyRenderer(renderer); \
    SDL_DestroyWindow(window);     \
    SDL_Quit();

#define SDL_DRAW                                                \
    SDL_LockSurface(screen);                                    \
    if (render(screen, graphics_buffer, field, S, H, W) != 0) { \
        cerr << "cuda error" << endl;                           \
        S = 0;                                                  \
        continue;                                               \
    }                                                           \
    SDL_UnlockSurface(screen);                                  \
    SDL_UpdateTexture(texture, NULL,                            \
                      screen->pixels,                           \
                      screen->pitch);                           \
    SDL_RenderClear(renderer);                                  \
    SDL_RenderCopy(renderer, texture, NULL, NULL);              \
    SDL_RenderPresent(renderer);

#define SDL_QUIT_EVENT_HANDLER         \
    SDL_Event event;                   \
    if (SDL_PollEvent(&event) &&       \
        (event.type == SDL_QUIT ||     \
         (event.type == SDL_KEYDOWN && \
          event.key.keysym.sym == 'q'))) break;

#define SDL_WINDOW          \
    SDL_Renderer* renderer; \
    SDL_Surface* screen;    \
    SDL_Texture* texture;   \
    SDL_Window* window;     \
                            \
    uint32_t* graphics_buffer;

#else
#define SDL_BOILERPLATE ;
#define SDL_CHECK_INIT ;
#define SDL_DESTROY_QUIT ;
#define SDL_DRAW ;
#define SDL_QUIT_EVENT_HANDLER ;
#define SDL_WINDOW ;

#endif

#endif
