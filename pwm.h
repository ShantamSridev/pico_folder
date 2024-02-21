#ifndef PWM_H
#define PWM_H

#include "pindefs.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

extern volatile uint slice_num;
extern volatile uint32_t wrap_value;

void pwm_out(float duty_cycle_percentage);

void init_pwm();

#endif