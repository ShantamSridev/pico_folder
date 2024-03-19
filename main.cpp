#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pico/multicore.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/adc.h"
#include "modules/pico-onewire/api/one_wire.h"

#include "structure.h"


// .----------------------------------------------------------.
// | Core 1 code                                              |
// `----------------------------------------------------------'

void core1_main() {
    printf("I2C Slave Example\n");
    setup_slave();
    // memset(context.mem, 0, sizeof(context.mem));
    // uint8_t sourceArray[] = {66, 3, 51, 51, 255,255, 255};
    // memcpy(context.mem, sourceArray, 7 * sizeof(uint8_t));
    //memset(context.mem, 0xFF, sizeof(context.mem));

    while (true) {
        // int y = context.mem_address;
        // printf("\n");
        // for (int i = 0; i < 10; i++) {
        //     printf("%02x ", context.mem[i]); // Print byte in hex format, padded with zeros
        // }
        // printf("\n"); // New line after printing all bytes
        // sleep_ms(1000);
    }
}

// .----------------------------------------------------------.
// | Core 0 code                                              |
// `----------------------------------------------------------'

int main(void){
    stdio_init_all();
    multicore_launch_core1(core1_main);
    adc_init();
    init_pwm();
    init_encoder();
    init_currentsensor();
    
    One_wire one_wire(ONE_WIRE_BUS);
    one_wire.init();
    rom_address_t address{};

    MyPID pid = MyPID(1,1,0);
    MyAngle angle;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    pid.setTarget(0);
    pid.run();

    while (true) {
        process_from_fifo(pid, angle);
        sleep_ms(100); // Adjust based on your needs
    }

    // // Initialize stdio for output
    // stdio_init_all();
    // adc_init();

    // init_pwm();
    // init_encoder();
    // init_currentsensor();
    
    // One_wire one_wire(ONE_WIRE_BUS);
    // one_wire.init();
    // rom_address_t address{};

    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);

    // MyPID pid = MyPID(1,1,0);
    // pid.setTarget(0);
    // //pid.setOutputRampRate(1);
    // MyAngle angle;

    // // RingBuffer<float, 40> rb;

    // // rb.push(10.1);

    // // rb.push(5.1);

    // // float item;
    // double Requiredangle = 300;
    // // Main loop
    // while (true) {
    //     gpio_put(LED_PIN, 1);

    //     //printf("Encoder: %d\n",position);
    //     //printf("diff: %d\n",rev_check);

    //     angle.runAngleInit(pid);
    //     angle.setAngle(Requiredangle,pid);
    //     printf("Angle : %f\n", angle.getAngle());

    //     pid.setTarget(30);
    //     pid.run();
    //     sleep_ms(10000);

    //     printf("Angle : %f\n", angle.getAngle());

    //     sleep_ms(5000);

    //     printf("Angle : %f\n", angle.getAngle());

    //     pid.setTarget(0);
    //     pid.run();

    //     while(true){}
    //     //pid.run();

    //     //float velocity = calc_velocity();
    //     //printf("Velocity: %f\n", vel);

    //     //printf("Angle: %f\n",(float(position)/135)*360);

        

    //     // while(!rb.isEmpty()) {
    //     //     rb.pop(item);
    //     //     printf( "Popped: %f ",item);
    //     // }
        
    //     //printf("Temperature: %3.1foC\n", read_temp(one_wire, address));
    //     //printf("Current: %f\n", readCurrent());
    //     //printf("Voltage: %f\n", read_voltage());

    //     sleep_ms(100);
    // }
}