#ifndef FIELD_H
#define FIELD_H

#include <curand.h>
#include <curand_kernel.h>
#include <math.h>

#include "cuda.h"
#include "macros.h"

#define MAX 100

void initField(int *field, int H, int W, int fill);
void transition(int *field, int H, int W);

#endif