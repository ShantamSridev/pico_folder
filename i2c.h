#include "modules/pico_i2c_slave/i2c_slave/include/i2c_fifo.h"
#include "modules/pico_i2c_slave/i2c_slave/include/i2c_slave.h"
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pindefs.h"


void setup_slave();

// The slave implements a 256 byte memory. To write a series of bytes, the master first
// writes the memory address, followed by the data. The address is automatically incremented
// for each byte transferred, looping back to 0 upon reaching the end. Reading is done
// sequentially from the current memory address.
struct context;

// Our handler is called from the I2C ISR, so it must complete quickly. Blocking calls /
// printing to stdio may interfere with interrupt handling.
void i2c_slave_handler(i2c_inst_t, i2c_slave_event_t);

