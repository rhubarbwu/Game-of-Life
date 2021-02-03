#ifndef FIELD_CUDA_H
#define FIELD_CUDA_H

#include <math.h>

#include "colours.h"
#include "rules.h"

#define MAX 100

void init_field(unsigned *field, unsigned H, unsigned W, unsigned F);
void transition(unsigned *field, unsigned H, unsigned W);

#endif
