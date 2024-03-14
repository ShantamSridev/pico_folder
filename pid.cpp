
#include "pid.h"

volatile float multicore_mem[64];

MyPID::MyPID(double p, double i, double d) : PID(p,i,d){
    maxOutput = 48;
    minOutput = -48; //48 at 15V
    //outputRampRate = 0; //now can be set over function
    maxPWMOutput = 7.51;
    minPWMOutput = 2.51;
    init();
}

void MyPID::init(){
    PID.setOutputLimits(maxOutput);
    PID.setSetpoint(0);
}

void MyPID::setPIDParams(){
    PID.setP();
    multicore_mem[] = ; //Convert the mem buffer, convert to float put it onto the set P and hten put it into the multicore_mem biffer so that irt can be directly accessed by the requests.
    PID.SetI();
    PID.SetD();
}

void MyPID::setTarget(double target){
    PID.setSetpoint(target);
}

void MyPID::setOutputLimits(double min,double max){
    PID.setOutputLimits(min, max);
}

void MyPID::setOutputRampRate(double rate){
    PID.setOutputRampRate(rate);
}

double MyPID::getOutput(double velocity){
	velocityOutput = PID.getOutput(velocity);
    PWMOutput = mapValue(velocityOutput, minOutput, maxOutput, minPWMOutput, maxPWMOutput);
    return PWMOutput;
}

void MyPID::run(){
    float velocity = calc_velocity();
    double output = getOutput(velocity);
    pwm_out(output);
}

double MyPID::mapValue(double  input, double  inputStart, double  inputEnd, double  outputStart, double  outputEnd) {
    // Calculate the slope (m) of the line connecting the input and output ranges
    double  slope = (outputEnd - outputStart) / (inputEnd - inputStart);
    // Apply the linear transformation formula (y = mx + b)
    double  output = outputStart + slope * (input - inputStart);
    return output;
}