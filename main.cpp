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
    angle myAngle;
    //pid.setOutputRampRate(1);

    // RingBuffer<float, 40> rb;

    // rb.push(10.1);

    // rb.push(5.1);

    // float item;
    
    // Main loop
    while (true) {
        gpio_put(LED_PIN, 1);

        //printf("Encoder: %d\n",position);
        //printf("diff: %d\n",rev_check);

        myAngle.runAngle(pid);
        myAngle.setAngle(180,pid);
        // printf("Starting runAngle");
        // pid.setTarget(10);
        // pid.run();
        // while (flag){
        //   flag = (rev_check == 224 && pulse >= 2) ? false : true;
        //   printf("rev: %d\n",rev_check);
        // }
        // printf("Finished runAngle");
        // pid.setTarget(0);
        // pid.run();
        while (true){}
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