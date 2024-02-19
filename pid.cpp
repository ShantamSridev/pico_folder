
#include "pid.h"


MyPID::MyPID(double p, double i, double d) : PID(p,i,d){
    maxOutput = 35;
    outputRampRate = 0; //unset
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

double MyPID::getOutput(double velocity){
	double velocityOutput = PID.getOutput(velocity);
    double PWMOutput = mapValue(velocityOutput, -maxOutput, maxOutput, minPWMOutput, maxPWMOutput);
    return PWMOutput;
}

double MyPID::mapValue(double x, double x_min, double x_max, double y_min, double y_max) {
    return (y_max - y_min) * (x - x_min) / (x_max - x_min) + y_min;
}