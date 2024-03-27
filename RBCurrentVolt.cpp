#include "RBCurrentVolt.h"

void timer1_irq_handler() {
    hw_clear_bits(&timer_hw->intr, 1u << 0); // Clear interrupt for timer 0
    // Your code for the first timer, e.g., read from sensor 1

    // Read data from the sensor
    float CurrentData = readCurrent(); // Placeholder, replace with actual sensor reading code
    float VoltageData = read_voltage(); 

    // Push the data into the ring buffer
    RBCurrent.push(CurrentData);
    RBVoltage.push(VoltageData);

    // Clear the interrupt and reset the timer here if needed
    // This depends on your specific timer hardware and SDK
}


void set_timer_CurrAndVolt(uint32_t frequency) {
    uint timer_num = 0; // Timer 0
    uint32_t alarm_value = (uint32_t)12500000 / frequency; // Assuming system clock is 125MHz

    irq_set_exclusive_handler(TIMER_IRQ_0 + timer_num, timer1_irq_handler);
    irq_set_enabled(TIMER_IRQ_0 + timer_num, true);
    hw_set_bits(&timer_hw->inte, 1u << timer_num);
    timer_hw->alarm[timer_num] = alarm_value;
}