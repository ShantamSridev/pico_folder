#include <cstdio>

//Encoder Inputs
#define ENCA 17 // WHITE
#define ENCB 16  // YELLOW

//Temperature Sensor
#define ONE_WIRE_BUS 15 //Digital 5

//Current Sensor
#define CURRENT 28  //ADC2 pin 34

//Motor Driver Ouput
#define PWM_PIN 14

// ADC input pins
#define VOLTAGE_POSITIVE 26 //ADC0 pin 31
#define VOLTAGE_NEGATIVE 27 //ADC1 pin 32

//Inductive Sensor
#define INDUCTIVE 13 //GP9 pin 12

//Default LED
#define LED_PIN 25





// I2C slave configuration
//#define I2C_SLAVE_ADDRESS 0x17 //TEST I2C Address PICO NORMAL
#define I2C_SLAVE_ADDRESS 0x3E //TEST I2C Address PICO W
#define I2C_BAUDRATE 400000 // 400 kHz


// For this example, we run both the master and slave from the same board.
// You'll need to wire pin GP4 to GP6 (SDA), and pin GP5 to GP7 (SCL).
#define I2C_SLAVE_SDA_PIN 2     // 4
#define I2C_SLAVE_SCL_PIN 3     // 5



#define PID_BUF_START 5