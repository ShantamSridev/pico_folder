#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include <stdio.h>


/// \tag::voltmeter-i2c[]

#define UART_ID uart1
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// UART pins
#define UART_TX_PIN 4
#define UART_RX_PIN 5

#define I2C_ADDR 0x3E

// Whch pin to monitor - default to 0
static int adc_pin = 0;

// conversion factor is into mili volts
const float conversion_factor=3.3f*1000/(1<<12);


int main() {
    // setup ADC
    stdio_init_all();

    // i2c setup
    i2c_init(i2c1, 400000);
    i2c_set_slave_mode(i2c1, true, I2C_ADDR);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);


    uint8_t rxdata[4];
    uint8_t txdata[2];
    char message[20];
    while (true) {
        // Receive data from controller
        // 3 bytes received - byte 0 is cmd (used as lower byte) byte 2 is higher - byte 3 is 0
           if (i2c_get_read_available(i2c1) < 3) continue;
        i2c_read_raw_blocking (i2c1, rxdata, 3);
        sleep_us(110);
        
        // Respond with ADC value (in milivolts)
        uint16_t adc_value=10;
        // Note that this will drop fraction rather than round, but close enough
        int value = 10;
        txdata[0] = value & 0xFF;
        txdata[1] = value >> 8;
        // Sends data in mv (as int)
        i2c_write_raw_blocking(i2c1, txdata, 2);
        
    }
}
