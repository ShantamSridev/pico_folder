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

#include "pindefs.h"
#include "i2c.h"
#include "structure.h"
#include "ringbuffer.h"
#include "pwm.h"
#include "onewire.h"
#include "encoder.h"
#include "velocity.h"
#include "current.h"
#include "voltage.h"
#include "pid.h"
#include "angle.h"



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

    while (true) {
        process_from_fifo(pid, angle);
        sleep_ms(5000); // Adjust based on your needs
    }
}