#include "pindefs.h"
#include <cstdio>

//#include "Ringbuffer.h"
#include "ringbuffer.h"
#include "pwm.h"
#include "onewire.h"
#include "encoder.h"
#include "velocity.h"
#include "current.h"
#include "voltage.h"
#include "pid.h"

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/adc.h"
#include "modules/pico-onewire/api/one_wire.h"

volatile int position = 0;
// globals
long prevTime= 0;
int positionPrev = 0;
float target_velocity = 20;
volatile int last_pos = 0;
volatile float difference = 0;


void isr_pin_a(uint gpio, uint32_t events) {
    bool stateB = gpio_get(ENCB); // Read the current state of pin B
    int i = 0;
    if(stateB>0) {
        i++; // Moving in one direction
    } else {
        i--; // Moving in the opposite direction
    }
    position = position + i;
    //printf("Encoder: %d\n",position);
}

void isr_pin_b(uint gpio, uint32_t events) { //134.4 pulses per motor revolution and using 1.6:1 belt ratio
 //gives 215 pulses per revolution of wheel

    difference = position - last_pos;
    last_pos = position;
    //position = 0;
}

void init_encoder() {
    // Initialize GPIO pins for encoder A and B as inputs
    gpio_init(ENCA);
    gpio_set_dir(ENCA, GPIO_IN);
    gpio_pull_up(ENCA); // Optional: enable pull-up if necessary

    gpio_init(ENCB);
    gpio_set_dir(ENCB, GPIO_IN);
    gpio_pull_up(ENCB); // Optional: enable pull-up if necessary

    // Configure interrupt for pin A to trigger on rising edge
    // gpio_set_irq_enabled_with_callback(ENCA, GPIO_IRQ_EDGE_RISE, true, &isr_pin_a);
    // gpio_set_irq_enabled(ENCA, GPIO_IRQ_EDGE_RISE, true);
    // gpio_set_irq_callback(&isr_pin_a);
    // if (true) irq_set_enabled(IO_IRQ_BANK0, true);

    gpio_init(INDUCTIVE);
    gpio_set_dir(INDUCTIVE, GPIO_IN);
    //gpio_pull_up(INDUCTIVE); // Optional: enable pull-up if necessary

    // // Configure interrupt for pin INDUCTIVE to trigger on rising edge
    // gpio_set_irq_enabled_with_callback(INDUCTIVE, GPIO_IRQ_EDGE_RISE, true, &isr_pin_b);

    gpio_set_irq_enabled(ENCA, GPIO_IRQ_EDGE_RISE, 1);
    gpio_set_irq_enabled(INDUCTIVE, GPIO_IRQ_EDGE_RISE, 1);
    gpio_add_raw_irq_handler(ENCA, &isr_pin_a);
    gpio_add_raw_irq_handler(INDUCTIVE, &isr_pin_b);
    irq_set_enabled(IO_IRQ_BANK0, true);
}

int main() {
  // Initialize stdio for output
    stdio_init_all();
    adc_init();

    init_pwm();
    init_encoder();
    init_currentsensor();
    
    One_wire one_wire(ONE_WIRE_BUS);
    one_wire.init();
    rom_address_t address{};

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    MyPID pid = MyPID(1.5,1,0);
    pid.setTarget(37);

    RingBuffer<float, 40> rb;

    rb.push(10.1);

    rb.push(5.1);

    float item;
    
    // Main loop
    while (true) {
        gpio_put(LED_PIN, 1);
        //printf("Check\n");
        printf("Encoder: %d\n",position);
        printf("diff: %f\n",difference);
        //float velocity = calc_velocity(position, prevTime, positionPrev);
        //double output = pid.getOutput(velocity);
        //printf("Output: %f\n", output);
        //pwm_out(output);
        //printf("Angle: %f\n",(float(position)/135)*360);
        //printf("Velocity: %f\n", velocity);
        // while(!rb.isEmpty()) {
        //     rb.pop(item);
        //     printf( "Popped: %f ",item);
        // }
        //printf("Velocity: %f\n", calc_velocity(position, prevTime, positionPrev));
        //printf("Temperature: %3.1foC\n", read_temp(one_wire, address));
        //printf("Current: %f\n", readCurrent());
        //printf("Voltage: %f\n", read_voltage());

        sleep_ms(100);
    }
}