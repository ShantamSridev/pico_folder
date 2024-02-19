//#include "Ringbuffer.h"
#include <cstdio>
#include "pwm.h"
#include "onewire.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "modules/pico-onewire/api/one_wire.h"

#define ENCA 2  // WHITE
#define ENCB 3  // YELLOW
#define PWM 5   //Output
#define ONE_WIRE_BUS 5 //Digital 5
#define CURRENT 1
#define PWM_PIN 14

int main() {
  // Initialize stdio for output
    stdio_init_all();

    init_pwm(PWM_PIN);
    init_onewire(ONE_WIRE_BUS);

    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Main loop
    while (true) {
        pwm_out(30);
        gpio_put(LED_PIN, 1);
        printf("Check");
        printf("Temperature: %3.1foC\n", read_temp());
        sleep_ms(1000);
    }
}
