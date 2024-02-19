//#include "Ringbuffer.h"
#include "pindefs.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

uint slice_num;
uint32_t wrap_value;

void pwm_out(float duty_cycle_percentage){
    uint32_t duty_cycle = (duty_cycle_percentage * wrap_value) / 100;

            // Set the PWM channel A duty cycle
            pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle);
}

void init_pwm(){
    // Initialize GPIO for PWM
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    // Get the PWM slice number for the PWM_PIN
    slice_num = pwm_gpio_to_slice_num(PWM_PIN);

    // Set PWM frequency
    // Calculate the required clock divider to achieve a 50Hz PWM signal
    // The PWM clock base frequency is 125MHz
    wrap_value = 40000; // This is an arbitrary choice to demonstrate the concept

    // The clock divider can be calculated as follows for a base clock of 125MHz
    float clkdiv = 125000000.0f / (50 * (wrap_value + 1));

    pwm_set_clkdiv(slice_num, clkdiv);
    pwm_set_wrap(slice_num, wrap_value);
    pwm_set_enabled(slice_num, true); // Enable PWM

    pwm_out(5);

}