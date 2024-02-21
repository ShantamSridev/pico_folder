#include "pindefs.h"
#include <cstdio>

#include "ringbuffer.h"
#include "pwm.h"
#include "onewire.h"
#include "encoder.h"
#include "velocity.h"
#include "current.h"
#include "voltage.h"
#include "pid.h"

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/adc.h"
#include "modules/pico-onewire/api/one_wire.h"


int main() {
  // Initialize stdio for output
    stdio_init_all();
    adc_init();

    init_pwm();
    init_encoder();
    init_currentsensor();
    
    One_wire one_wire(ONE_WIRE_BUS);
    one_wire.init();
    rom_address_t address{};

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    MyPID pid = MyPID(1.5,1,0);
    pid.setTarget(37);

    RingBuffer<float, 40> rb;

    rb.push(10.1);

    rb.push(5.1);

    float item;
    
    // Main loop
    while (true) {
        gpio_put(LED_PIN, 1);
        //printf("Check\n");
        //printf("Encoder: %d\n",position);
        //printf("diff: %f\n",difference);
        pid.run();
        //printf("Angle: %f\n",(float(position)/135)*360);
        //printf("Velocity: %f\n", velocity);
        // while(!rb.isEmpty()) {
        //     rb.pop(item);
        //     printf( "Popped: %f ",item);
        // }
        //printf("Velocity: %f\n", calc_velocity(position, prevTime, positionPrev));
        //printf("Temperature: %3.1foC\n", read_temp(one_wire, address));
        //printf("Current: %f\n", readCurrent());
        //printf("Voltage: %f\n", read_voltage());

        sleep_ms(100);
    }
}