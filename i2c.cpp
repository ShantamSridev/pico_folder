#include "i2c.h"

volatile I2CContext context;

// Callback for when data is received from the master
void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    static size_t index = 0;

    switch (event) {
        case I2C_SLAVE_RECEIVE:
            // Read the data from master
            while (i2c_get_read_available(i2c)){
                if (context.mem_address_written){
                    uint8_t temp = i2c_read_byte_raw(i2c);
                    context.mem[context.mem_address] = temp;
                    context.mem_address++;
                    printf("$ %02x\n", context.mem_address);
                    sleep_us(1);
                }
                else{
                    context.mem_address = i2c_read_byte_raw(i2c);
                    printf("address = %02x\n", context.mem_address);
                    context.mem_address_written = true;
                    add_to_fifo(context.mem_address); 
                }
            }
            break;

        case I2C_SLAVE_REQUEST:
            // load from memory
            //getstruct(context.mem_address);
            context.mem_address = 224; //DOES NOT WORK CUZ CANT INCREMENT
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


void setup_slave(){
    // i2c setup

    i2c_init(i2c1, I2C_BAUDRATE);
    gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SDA_PIN);
    gpio_pull_up(I2C_SLAVE_SCL_PIN);
    i2c_slave_init(i2c1, I2C_SLAVE_ADDRESS, &i2c_slave_handler);
}


// float memToFloat(uint8_t address) {
//     if (address + 4 > sizeof(context.mem)) {
//         printf("out of range address: memToFloat()")
//     }

//     float result;
//     // Copy bytes starting from the given address into the float variable
//     std::memcpy(&result, &context.mem[address], sizeof(result));
//     return result;
// }

float memToFloat(uint8_t address) {
    if (address + 4 > sizeof(context.mem)) {
        // Handle error, e.g., return 0, set an error flag, etc.
    }

    float result;
    // Cast away the 'volatile' (with caution)
    const void* source = const_cast<const void*>(reinterpret_cast<const volatile void*>(&context.mem[address]));
    std::memcpy(&result, source, sizeof(result));
    return result;
}