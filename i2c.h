#ifndef I2C_H
#define I2C_H

#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pindefs.h"
#include <cstdio>
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>

// The slave implements a 256 byte memory. To write a series of bytes, the master first
// writes the memory address, followed by the data. The address is automatically incremented
// for each byte transferred, looping back to 0 upon reaching the end. Reading is done
// sequentially from the current memory address.

static struct
{
    uint8_t mem[256]; //CAN JUST MAKE THIS LARGER AND WRITE DIRECTLY INTO THIS FOR RING VARIABLES
    uint8_t mem_address;
    uint8_t mem_payload[4];
    uint8_t mem_comm[5];
    bool mem_address_written;
} context;


// Our handler is called from the I2C ISR, so it must complete quickly. Blocking calls /
// printing to stdio may interfere with interrupt handling.
void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event);

void setup_slave();

#endif