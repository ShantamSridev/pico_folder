#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <pico/stdlib.h>
#include <stdio.h>
#include "pico/multicore.h"
#include <array>
#include <atomic>

#include "pindefs.h"
#include "i2c.h"
#include "structure.h"
#include "ringbuffer.h"
#include "pwm.h"
#include "onewire.h"
#include "encoder.h"
#include "velocity.h"
#include "current.h"
#include "voltage.h"
#include "pid.h"
#include "angle.h"

class MyPID;
class MyAngle;

// Define the size of the FIFO
constexpr size_t FIFO_SIZE = 2;

// Shared FIFO structure
struct SharedFIFO {
    std::array<int, FIFO_SIZE> buffer; // buffer for FIFO multicore messaging
    std::atomic<size_t> writeIndex = {0};
    std::atomic<size_t> readIndex = {0};
};

// Declare the shared FIFO instance
extern SharedFIFO fifo;


void process_from_fifo(MyPID& pid, MyAngle& angle);


void add_to_fifo(int item);


void getstruct(uint8_t addin, MyPID& pid, MyAngle& angle);
void getReqstruct(uint8_t addin);


#endif