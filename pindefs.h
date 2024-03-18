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


//I2C MEMORY ADDRESSES

//MOTION
#define I2C_GET_ANGLE 4
#define I2C_SETANGLE 16
#define I2C_SETSPEED 20

//PID
#define I2C_SETP 24
#define I2C_SETI 28
#define I2C_SETD 32
#define I2C_SETPIDRATE 36
#define I2C_SETPIDUP 40
#define I2C_SETPIDLOW 44

#define I2C_SETFREQTEMP 116
#define I2C_SETLENGTHTEMP 120
#define I2C_SETFREQ_A_V 132
#define I2C_SETLENGTH_A_V 136

//CHECK THE CHATGPT FOR THE TIMER FIRING AT FIXED FREQUENCY



#define I2C_REQANGLE 8
#define I2C_REQSPEED 12