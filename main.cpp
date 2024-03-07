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
uint8_t address;
float value;

// The slave implements a 256 byte memory. To write a series of bytes, the master first
// writes the memory address, followed by the data. The address is automatically incremented
// for each byte transferred, looping back to 0 upon reaching the end. Reading is done
// sequentially from the current memory address.
static struct
{
    uint8_t mem[256]; //CAN JUST MAKE THIS LARGER AND WRITE DIRECTLY INTO THIS FOR RING VARIABLES
    uint8_t mem_address;
    bool mem_address_written;
} context;

 uint8_t data[32];

// Our handler is called from the I2C ISR, so it must complete quickly. Blocking calls /
// printing to stdio may interfere with interrupt handling.
static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch (event) {
    case I2C_SLAVE_RECEIVE: // master has written some data
        if (!context.mem_address_written) {
            // writes always start with the memory address
            uint8_t buf[2];
            i2c_read_raw_blocking(i2c, buf, 2);
            address = buf[0];
            address = context.mem_address;
            value = buf[1];
            context.mem_address_written = true;
            //sleep_us(110);
        } else {
            // save into memory
            context.mem[context.mem_address] = i2c_read_byte_raw(i2c);
            context.mem_address++;
        }
        break;
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
        context.mem_address++;
        break;
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

    i2c_init(i2c1, 400000);
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
        printf("address = %d\n",address);
        printf("value = %f\n",value);
        sleep_ms(1000);
    }
}
