#include <curand.h>
#include <curand_kernel.h>
#include <math.h>

#include "cuda.h"
#include "macros.h"

#define MAX 100

void allocField(int *field, int H, int W);
void freeField(int *field, int H, int W);
void initField(int *field, int H, int W, int fill);
void transition(int *field, int H, int W);