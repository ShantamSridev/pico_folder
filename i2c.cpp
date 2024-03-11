#include "i2c.h"


// static struct
// {
//     uint8_t mem[256]; //CAN JUST MAKE THIS LARGER AND WRITE DIRECTLY INTO THIS FOR RING VARIABLES
//     uint8_t mem_address;
//     uint8_t mem_payload[4];
//     uint8_t mem_comm[5];
//     bool mem_address_written;
// } context;

// void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
//     switch (event) {
//     case I2C_SLAVE_RECEIVE: // master has written some data
//         if (!context.mem_address_written) {
//             // writes always start with the memory address
//             context.mem_address = i2c_read_byte(i2c);
//             context.mem_address_written = true;
//         } else {
//             // save into memory
//             context.mem[context.mem_address] = i2c_read_byte(i2c);
//             printf("%d\n", context.mem[context.mem_address]);
//             context.mem_address++;
//         }
//         break;
//     case I2C_SLAVE_REQUEST: // master is requesting data
//         // load from memory
//         i2c_write_byte(i2c, context.mem[context.mem_address]);
//         context.mem_address++;
//         break;
//     case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
//         context.mem_address_written = false;
//         break;
//     default:
//         break;
//     }
// }

// void setup_slave() {
//     gpio_init(I2C_SLAVE_SDA_PIN);
//     gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
//     gpio_pull_up(I2C_SLAVE_SDA_PIN);

//     gpio_init(I2C_SLAVE_SCL_PIN);
//     gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
//     gpio_pull_up(I2C_SLAVE_SCL_PIN);

//     i2c_init(i2c0, I2C_BAUDRATE);
//     // configure I2C0 for slave mode
//     i2c_slave_init(i2c0, I2C_SLAVE_ADDRESS, &i2c_slave_handler);
// }

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


void setup_slave(){
    // i2c setup

    i2c_init(i2c1, I2C_BAUDRATE);
    gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SDA_PIN);
    gpio_pull_up(I2C_SLAVE_SCL_PIN);
    i2c_slave_init(i2c1, I2C_SLAVE_ADDRESS, &i2c_slave_handler);
}