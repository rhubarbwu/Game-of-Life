#ifndef FIELD_H
#define FIELD_H

#include <stdlib.h>
#include <time.h>

#include "colours.h"
#include "rules.h"

void init_field(unsigned *field, unsigned H, unsigned W, unsigned fill);
void transition(unsigned *field, unsigned H, unsigned W);

#endif
