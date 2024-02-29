#include "pindefs.h"
#include <cstdio>

#include "i2c.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

int main() {
  // Initialize stdio for output
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_put(LED_PIN, 1);

    setup_slave();
}