#ifndef VELOCITY_H
#define VELOCITY_H

#include "pindefs.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "encoder.h"

extern volatile long prevTime;
extern volatile int positionPrev;
//volatile float target_velocity = 20;

float calc_velocity();

#endif // VELOCITY_H