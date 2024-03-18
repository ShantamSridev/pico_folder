#ifndef CURRENT_H
#define CURRENT_H

#include "pindefs.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"

void init_currentsensor();

float readCurrent();

#endif