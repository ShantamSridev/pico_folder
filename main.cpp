#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pico/multicore.h"
#include "i2c.h"

#include "pico/stdlib.h"
#include "hardware/i2c.h"   

// const uint8_t DATA_TO_SEND[32] = {/* Initialize with your data */};
// uint8_t received_data[5];

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
        // printf("address = %d\n",command_address);
        // printf("value = %f\n",command_data);
        int y = context.mem_address;
        printf("\n");
        for (int i = 0; i < 10; i++) {
            printf("%02x ", context.mem[i]); // Print byte in hex format, padded with zeros
        }
        printf("\n"); // New line after printing all bytes
        sleep_ms(1000);
    }
}

// .----------------------------------------------------------.
// | Core 0 code                                              |
// `----------------------------------------------------------'

int main(void){
    stdio_init_all();
    multicore_launch_core1(core1_main);

    while (true) {
    //     // printf("address = %d\n",command_address);
    //     // printf("value = %f\n",command_data);
    //     int y = context.mem_address;
    //     printf("\n");
    //     for (int i = 0; i < 10; i++) {
    //         printf("%02x ", context.mem[i]); // Print byte in hex format, padded with zeros
    //     }
    //     printf("\n"); // New line after printing all bytes
    //     sleep_ms(1000);
    }
}