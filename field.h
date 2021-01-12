#ifndef FIELD_H
#define FIELD_H

#include <stdlib.h>
#include <time.h>

#include "macros.h"

void initField(unsigned *field, unsigned H, unsigned W, unsigned fill);
void transition(unsigned *field, unsigned H, unsigned W);

#endif