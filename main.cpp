#include "pindefs.h"
#include <cstdio>

//#include "Ringbuffer.h"
#include "pwm.h"
#include "onewire.h"
#include "encoder.h"
#include "velocity.h"
#include "current.h"

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/adc.h"

// #include <OneWire.h>
// #include <DallasTemperature.h>

int position = 0;
// globals
long prevTime= 0;
int positionPrev = 0;

// OneWire oneWire(ONE_WIRE_BUS);  
// DallasTemperature sensors(&oneWire);


void isr_pin_a(uint gpio, uint32_t events) {
    bool stateB = gpio_get(ENCB); // Read the current state of pin B
    int i = 0;
    if(stateB>0) {
        i++; // Moving in one direction
    } else {
        i--; // Moving in the opposite direction
    }
    position = position +i;
}

void init_encoder() {
    // Initialize GPIO pins for encoder A and B as inputs
    gpio_init(ENCA);
    gpio_set_dir(ENCA, GPIO_IN);
    gpio_pull_up(ENCA); // Optional: enable pull-up if necessary

    gpio_init(ENCB);
    gpio_set_dir(ENCB, GPIO_IN);
    gpio_pull_up(ENCB); // Optional: enable pull-up if necessary

    // Configure interrupt for pin A to trigger on both rising and falling edges
    gpio_set_irq_enabled_with_callback(ENCA, GPIO_IRQ_EDGE_RISE, true, &isr_pin_a);
}


int main() {
  // Initialize stdio for output
    stdio_init_all();

    init_pwm();
    init_onewire();
    init_encoder();
    //sensors.begin();
    init_currentsensor();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Main loop
    while (true) {
        pwm_out(30);
        gpio_put(LED_PIN, 1);
        //printf("Check\n");
        //printf("Encoder: %d\n",position);
        //printf("Angle: %f\n",(float(position)/135)*360);
        printf("Velocity: %f\n", calc_velocity(position, prevTime, positionPrev));
        
        sleep_ms(100);
    }
}
