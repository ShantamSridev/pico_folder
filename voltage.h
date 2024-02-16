#include "pindefs.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <math.h>

// Voltage Divider Calculation
const float R1 = 27000.0; // R1 in Ohms
const float R2 = 5600.0; // R2 in Ohms
const float VOLTAGE_DIVIDER_RATIO = (R1 + R2) / R2;

// ADC Conversion Constants
const float ADC_CONVERSION_FACTOR = 3.3f / (1 << 12); // 12-bit ADC, 3.3V reference

void setup() {
    stdio_init_all();
    //adc_init();
    // Select ADC input 0 (GPIO 26) for positive voltage
    adc_gpio_init(VOLTAGE_POSITIVE);
    // Select ADC input 1 (GPIO 27) for negative voltage
    adc_gpio_init(VOLTAGE_NEGATIVE);
}

float read_voltage_single(uint pin) {
    adc_select_input(pin);
    uint16_t adc_value = adc_read();
    float voltage = adc_value * ADC_CONVERSION_FACTOR * VOLTAGE_DIVIDER_RATIO;
    return voltage;
}

float read_voltage(){
        float positive_voltage = read_voltage_single(0); // ADC channel for GPIO 26
        float negative_voltage = read_voltage_single(1); // ADC channel for GPIO 27

        if (positive_voltage > 0.1) { // Threshold to avoid noise
            printf("Voltage on positive pin: %.2f V\n", positive_voltage);
            return positive_voltage;
        } else if (negative_voltage > 0.1) {
            printf("Voltage on negative pin (inverted): %.2f V\n", -negative_voltage);
            return -negative_voltage;
        } else {
            printf("No significant voltage detected\n");
            return 0.0f;
        }
}
