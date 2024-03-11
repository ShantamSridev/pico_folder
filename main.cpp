#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>
#include "i2c.h"

#include "pico/stdlib.h"
#include "hardware/i2c.h"   

const uint8_t DATA_TO_SEND[32] = {/* Initialize with your data */};
uint8_t received_data[5];


int main() {    
    stdio_init_all();
    printf("I2C Slave Example\n");
    setup_slave();

    

    while (true) {
        // printf("address = %d\n",command_address);
        // printf("value = %f\n",command_data);
        int y = context.mem_address;
        printf("\n");
        for (int i = 5; i < 10; i++) {
            printf("%02x ", context.mem[i]); // Print byte in hex format, padded with zeros
        }
        printf("\n"); // New line after printing all bytes
        sleep_ms(1000);
    }
}
