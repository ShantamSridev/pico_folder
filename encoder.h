    #ifndef ENCODER_H
    #define ENCODER_H

    #include "pindefs.h"
    #include <cstdio>
    #include "pico/stdlib.h"
    #include "hardware/gpio.h"

    extern volatile int last_pos;
    extern volatile float difference;
    extern volatile int position;
    extern volatile int rev_check;

    void isr_pin_a();

    void isr_pin_b();
    void gpio_callback(uint gpio, uint32_t events);

    void init_encoder();

    #endif