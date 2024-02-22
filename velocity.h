#ifndef VELOCITY_H
#define VELOCITY_H

#include "pindefs.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "encoder.h"

extern volatile long prevTime;
extern volatile int positionPrev;
extern volatile double vel;
//volatile float target_velocity = 20;

double calc_velocity();

#endif // VELOCITY_H