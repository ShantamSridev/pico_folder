
#include "pid.h"


MyPID::MyPID(double p, double i, double d) : PID(p,i,d){
    maxOutput = 35;
    minOutput = -35;
    //outputRampRate = 0; //now can be set over function
    maxPWMOutput = 7.5;
    minPWMOutput = 2.5;
    init();
}

void MyPID::init(){
    PID.setOutputLimits(maxOutput);
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
    PWMOutput = mapValue(velocityOutput, -minOutput, maxOutput, minPWMOutput, maxPWMOutput);
    return PWMOutput;
}

double MyPID::mapValue(double x, double x_min, double x_max, double y_min, double y_max) {
    return (y_max - y_min) * (x - x_min) / (x_max - x_min) + y_min;
}