#ifndef RBCURRENTVOLT_H
#define RBCURRENTVOLT_H

#include "pindefs.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

#include "current.h"
#include "voltage.h"
#include "ringbuffer.h"

// Global or class-scoped ring buffer instance, properly initialized elsewhere
extern volatile RingBuffer<float> RBCurrent; 

extern volatile RingBuffer<float> RBVoltage; 

void timer1_irq_handler();

void set_timer_CurrAndVolt(uint32_t frequency);

#endif