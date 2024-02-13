//#include "Ringbuffer.h"
#include "Pwm.h"
//#include <util/atomic.h>  // For the ATOMIC_BLOCK macro
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pico-onewire/api/one_wire.h"

#define ENCA 2  // WHITE
#define ENCB 3  // YELLOW
#define PWM 5   //Output
#define ONE_WIRE_BUS 4 //Digital 4
#define CURRENT 1
#define PWM_PIN 14

int main() {
  // Initialize stdio for output
    stdio_init_all();

    init_pwm(PWM_PIN);

    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Main loop
    while (true) {
        pwm_out(30);
    }
}
