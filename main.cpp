#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

// I2C slave configuration
const uint I2C_SLAVE_ADDRESS = 0x17;
const uint8_t DATA_TO_SEND[32] = {/* Initialize with your data */};
uint8_t received_data[5];

static struct
{
    uint8_t mem[256]; //CAN JUST MAKE THIS LARGER AND WRITE DIRECTLY INTO THIS FOR RING VARIABLES
    uint8_t mem_address;
    uint8_t mem_payload[4];
    uint8_t mem_comm[5];
    bool mem_address_written;
} context;


// Callback for when data is received from the master
void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    static size_t index = 0;

    switch (event) {
        case I2C_SLAVE_RECEIVE:
            // Read the data from master
            while (i2c_get_read_available(i2c)){
                if (context.mem_address_written){
                    uint8_t temp = i2c_read_byte_raw(i2c);
                    if (temp !=  0xFF){
                        context.mem[context.mem_address] = temp;
                        context.mem_address++;
                        printf("$");
                        sleep_us(1);
                    }
                    else{
                        printf("requesting data");
                        printf("address for send = %02x\n ", context.mem_address);
                    }
                }
                else{
                    //i2c_read_raw_blocking (i2c1, context.mem_comm, 5);
                    //context.mem_address = context.mem_comm[0];
                    context.mem_address = i2c_read_byte_raw(i2c);
                    printf("address = %02x\n ", context.mem_address);
                    context.mem_address_written = true;
            }
            }
            break;

        case I2C_SLAVE_REQUEST:
            // load from memory
            printf("address for send = %02x\n ", context.mem_address);
            i2c_write_byte_raw(i2c, context.mem[context.mem_address]);
            context.mem_address++;
            break;

        case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
            context.mem_address_written = false;
            break;

        default:
            break;

    }
}

int main() {
    stdio_init_all();
    printf("I2C Slave Example\n");

    i2c_init(i2c1, 400000);
    //i2c_set_slave_mode(i2c1, true, I2C_ADDR);
    //i2c_set_slave_mode(i2c1, true, I2C_ADDR);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);
    i2c_slave_init(i2c1, I2C_SLAVE_ADDRESS, &i2c_slave_handler);

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
