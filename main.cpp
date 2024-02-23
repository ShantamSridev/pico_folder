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
#include "angle.h"

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

    MyPID pid = MyPID(1,1,0);
    pid.setTarget(0);
    //pid.setOutputRampRate(1);
    MyAngle angle;

    // RingBuffer<float, 40> rb;

    // rb.push(10.1);

    // rb.push(5.1);

    // float item;
    double Requiredangle = 300;
    // Main loop
    while (true) {
        gpio_put(LED_PIN, 1);

        //printf("Encoder: %d\n",position);
        //printf("diff: %d\n",rev_check);

        angle.runAngleInit(pid);
        angle.setAngle(Requiredangle,pid);

        pid.setTarget(30);
        pid.run();
        sleep_ms(10000);

        printf("Angle : %f\n", angle.getAngle());

        sleep_ms(5000);

        printf("Angle : %f\n", angle.getAngle());

        pid.setTarget(0);
        pid.run();

        while(true){}
        //pid.run();

        //float velocity = calc_velocity();
        //printf("Velocity: %f\n", vel);

        //printf("Angle: %f\n",(float(position)/135)*360);

        

        // while(!rb.isEmpty()) {
        //     rb.pop(item);
        //     printf( "Popped: %f ",item);
        // }
        
        //printf("Temperature: %3.1foC\n", read_temp(one_wire, address));
        //printf("Current: %f\n", readCurrent());
        //printf("Voltage: %f\n", read_voltage());

        sleep_ms(100);
    }
}