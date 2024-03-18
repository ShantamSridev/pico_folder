#ifndef CURRENT_H
#define CURRENT_H

#include "pindefs.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"

void init_currentsensor(){
    //ADC SETUP
    //adc_init();
    adc_gpio_init(CURRENT); // Initialize GPIO 26 for ADC
    adc_select_input(2); // Select ADC input 0
}

float readCurrent(){
  float val = adc_read();  // read the input pin
  //float voltage = val * 3.3f / 4095.0f;
  float current = (val - 2047.5f)*(39.0f/2047.5f); //CURRENT SENSOR
  return current;
}

#endif