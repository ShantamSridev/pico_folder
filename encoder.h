#include "pindefs.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

volatile int last_pos = 0;
volatile float difference = 0;
volatile int position = 0;

void isr_pin_a() {
    bool stateB = gpio_get(ENCB); // Read the current state of pin B
    int i = 0;
    if(stateB>0) {
        i++; // Moving in one direction
    } else {
        i--; // Moving in the opposite direction
    }
    position = position + i;
}

void isr_pin_b() { //134.4 pulses per motor revolution and using 1.6:1 belt ratio
 //gives 215 pulses per revolution of wheel

    long newT = time_us_32();
    difference = position - last_pos;
    last_pos = position;
    position = 0;
}

void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == ENCA) {
        isr_pin_a();
    } else if (gpio == INDUCTIVE) {
        isr_pin_b();
    }
}

void init_encoder() {
    // Initialize GPIO pins for encoder A and B as inputs
    gpio_init(ENCA);
    gpio_set_dir(ENCA, GPIO_IN);
    gpio_pull_up(ENCA); // Optional: enable pull-up if necessary

    gpio_init(ENCB);
    gpio_set_dir(ENCB, GPIO_IN);
    gpio_pull_up(ENCB); // Optional: enable pull-up if necessary

    // Configure interrupt for pin A to trigger on rising edge
    gpio_set_irq_enabled_with_callback(ENCA, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    // gpio_set_irq_enabled(ENCA, GPIO_IRQ_EDGE_RISE, true);
    // gpio_set_irq_callback(&isr_pin_a);
    // if (true) irq_set_enabled(IO_IRQ_BANK0, true);

    gpio_init(INDUCTIVE);
    gpio_set_dir(INDUCTIVE, GPIO_IN);
    gpio_pull_up(INDUCTIVE); // Optional: enable pull-up if necessary

    // // Configure interrupt for pin INDUCTIVE to trigger on rising edge
    gpio_set_irq_enabled_with_callback(INDUCTIVE, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);

    // gpio_set_irq_enabled(ENCA, GPIO_IRQ_EDGE_RISE, 1);
    // gpio_set_irq_enabled(INDUCTIVE, GPIO_IRQ_EDGE_RISE, 1);
    // gpio_add_raw_irq_handler(ENCA, isr_pin_a);
    // gpio_add_raw_irq_handler(INDUCTIVE, isr_pin_b);
    // irq_set_enabled(IO_IRQ_BANK0, true);
}