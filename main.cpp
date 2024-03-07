#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>

static const uint I2C_SLAVE_ADDRESS = 0x17;
static const uint I2C_BAUDRATE = 400000; // 400 kHz

//#ifdef i2c_default
// For this example, we run both the master and slave from the same board.
// You'll need to wire pin GP4 to GP6 (SDA), and pin GP5 to GP7 (SCL).
static const uint I2C_SLAVE_SDA_PIN = PICO_DEFAULT_I2C_SDA_PIN; // 4
static const uint I2C_SLAVE_SCL_PIN = PICO_DEFAULT_I2C_SCL_PIN; // 5

float main_buf[256];
float command_data;
int command_address;


static struct
{
    uint8_t mem[256]; //CAN JUST MAKE THIS LARGER AND WRITE DIRECTLY INTO THIS FOR RING VARIABLES
    uint8_t mem_address;
    uint8_t mem_payload[4];
    uint8_t mem_comm[8];
    bool mem_address_written;
} context;


int pack_int(uint8_t *val) {
    uint32_t data =     ((uint32_t)val[3] << 24) | 
                        ((uint32_t)val[2] << 16) |
                        ((uint32_t)val[1] << 8)  |
                        (uint32_t)val[0];

    return int(data);
}

float pack_float(uint8_t *val) {
    float result;
    memcpy(&result, val, sizeof(result));
    return result;
}

static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch (event) {
    case I2C_SLAVE_RECEIVE: // master has written some data
        if (!context.mem_address_written) {
            // writes always start with the memory address
            context.mem_address = i2c_read_byte_raw(i2c);
            printf("address = %u\n",context.mem_address);
            context.mem_address_written = true;
        } else {
            // save into memory
            context.mem[context.mem_address] = i2c_read_byte_raw(i2c);
            context.mem_address++;
        }
        break;
    // case I2C_SLAVE_RECEIVE: // master has written some data
    // if (!context.mem_address_written) {

    //     i2c_read_raw_blocking(i2c, context.mem_comm, 8);
    //     //context.mem_address_written = true;
    //     // command_address = pack_int(context.mem_address);
    //     // i2c_read_raw_blocking(i2c, context.mem_payload, 4);
    //     // command_data = pack_float(context.mem_payload);
    //     command_address = pack_int(context.mem_comm);
    //     command_data = pack_float(&context.mem_comm[4]);

    // }
    // break;
    // case I2C_SLAVE_RECEIVE: // master has written some data
    //     if (!context.mem_address_written) {
    //         // writes always start with the memory address
    //         uint8_t buf[2];
    //         i2c_read_raw_blocking(i2c, buf, 2);
    //         address = buf[0];
    //         address = context.mem_address;
    //         value = buf[1];
    //         context.mem_address_written = true;
    //         //sleep_us(110);
    //     } else {
    //         // save into memory
    //         context.mem[context.mem_address] = i2c_read_byte_raw(i2c);
    //         context.mem_address++;
    //     }
    //     break;
    case I2C_SLAVE_REQUEST: // master is requesting data
        // load from memory
        //YOU KNOW mem_address, run it through A CHECKER AND RETRIEVE DATA, OR DIRECTLY READ FROM A LARGER MEM
        // if (startAddress < 0 || startAddress > 256 - 32) {
        //     // Handle error: startAddress out of bounds
        //     return;
        // }
        // memcpy destination to source, for 32 bytes (which is 8 floats)
        // Since memcpy works with bytes, it doesn't matter here that we're copying into float array
            // memcpy(data, mem+context.mem_address, 32);
            // i2c_write_raw_blocking(i2c, data,32 );
        //

        // // load from memory
        // i2c_write_byte_raw(i2c, context.mem[context.mem_address]);
        // context.mem_address++;
        // break;

    case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
        context.mem_address_written = false;
        //SHOULD PUT THE DATA NOW INTO ANOTHER DATA VECTOR TO BE USED OR MAKE THE mem BIGGER
        break;
    default:
        break;
    }
}

static void setup_slave() {
    // gpio_init(I2C_SLAVE_SDA_PIN);
    // gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
    // gpio_pull_up(I2C_SLAVE_SDA_PIN);

    // gpio_init(I2C_SLAVE_SCL_PIN);
    // gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
    // gpio_pull_up(I2C_SLAVE_SCL_PIN);

    // i2c_init(i2c1, I2C_BAUDRATE);
    // // configure I2C0 for slave mode

    // i2c_init(i2c1, I2C_BAUDRATE);
    // // configure I2C0 for slave mode

    i2c_init(i2c1, 400000);
    //i2c_set_slave_mode(i2c1, true, I2C_ADDR);
    //i2c_set_slave_mode(i2c1, true, I2C_ADDR);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);
    i2c_slave_init(i2c1, I2C_SLAVE_ADDRESS, &i2c_slave_handler);
}

int main() {
    stdio_init_all();

    setup_slave();
    while(1){
        // printf("address = %d\n",command_address);
        // printf("value = %f\n",command_data);
        for (int i = 5; i < (9); i++) {
            printf("%02x ", context.mem[i]); // Print byte in hex format, padded with zeros
        }
        printf("\n"); // New line after printing all bytes
        sleep_ms(1000);
    }
}