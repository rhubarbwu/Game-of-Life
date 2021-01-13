#ifndef GRAPHICS_CUDA_H
#define GRAPHICS_CUDA_H

#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>

#include <iostream>

#include "colours.h"
#include "macros.h"

__device__ const unsigned COLOURS[5] = GREEN;

uint32_t* gpuAlloc(unsigned screen_size);
void gpuFree(void* gpu_mem);
unsigned gpuBlit(void* src, void* dst, unsigned screen_size);
void render(SDL_Surface* screen,
            void* cuda_pixels,
            unsigned* field, unsigned S, unsigned H, unsigned W);

#endif
