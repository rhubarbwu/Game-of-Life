#ifndef FIELD_CUDA_H
#define FIELD_CUDA_H

#include <curand.h>
#include <curand_kernel.h>
#include <math.h>

#include "cuda.h"
#include "macros.h"

#define MAX 100

void init_field(unsigned *field, unsigned H, unsigned W, unsigned F);
void transition(unsigned *field, unsigned H, unsigned W);

#endif