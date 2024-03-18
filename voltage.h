#ifndef VOLTAGE_H
#define VOLTAGE_H

#include "pindefs.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <math.h>

// Voltage Divider Calculation
const float R1 = 27000.0; // R1 in Ohms
const float R2 = 5600.0; // R2 in Ohms
const float VOLTAGE_DIVIDER_RATIO = (R1 + R2) / R2;

// ADC Conversion Constants
const float ADC_CONVERSION_FACTOR = 3.3f / (1 << 12); // 12-bit ADC, 3.3V reference

void setup();

float read_voltage_single(uint pin);

float read_voltage();

#endif