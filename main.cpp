/**
 * Raspberry Pi Pico - Voltmeter
 * Sends via i2c
 * Works with ADC pin 0
 * See: www.penguintutor.com/projects/pico
 */


#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "pico/multicore.h"


#define I2C_ADDR 0x3E

int main() {
    // setup ADC
    stdio_init_all();

    // i2c setup
    // i2c_init(i2c1, 10000);
    // i2c_set_slave_mode(i2c1, true, I2C_ADDR);
    // gpio_set_function(2, GPIO_FUNC_I2C);
    // gpio_set_function(3, GPIO_FUNC_I2C);
    // gpio_pull_up(2);
    // gpio_pull_up(3);
    
    uint8_t rxdata[4];
    uint8_t txdata[2];
    char message[20];
    while (true) {
        // Receive data from controller
        // 3 bytes received - byte 0 is cmd (used as lower byte) byte 2 is higher - byte 3 is 0
           if (i2c_get_read_available(i2c1) < 3) continue;
        i2c_read_raw_blocking (i2c1, rxdata, 3);
        //sprintf (message, "Rx: %d %d %d\r\n", rxdata[0], rxdata[1], rxdata[2]);
        //uart_puts(UART_ID, message);
        sprintf (message, "Value %d\r\n", rxdata[0]+(rxdata[1]<<8));

        // Note that this will drop fraction rather than round, but close enough
        int value = (int) 10;
        txdata[0] = value & 0xFF;
        txdata[1] = value >> 8;
        sprintf (message, "Tx: %d %d - %d\r\n", txdata[0], txdata[1], value);
        // Sends data in mv (as int)
        i2c_write_raw_blocking(i2c1, txdata, 2);
        
    }
}

/// \end:voltmeter-i2c[]
