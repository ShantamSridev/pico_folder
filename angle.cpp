#include "angle.h"

MyAngle::MyAngle(){
    flag = true;
}

double MyAngle::findAngle(){
    return rev_check/0.6222222222;
}

void MyAngle::runAngleInit(MyPID& control){
    printf("Starting runAngleInit\n");
        control.setTarget(10);
        control.run();
        while (flag){
          flag = (rev_check == 224 && pulse >= 2) ? false : true;
        }
        printf("Finished runAngleInit\n");
        control.setTarget(0);
        control.run();
}

void MyAngle::setAngle(double ReqAngle, MyPID& control){
    printf("Starting setAngle\n");
    control.setTarget(8);
    control.run();
    double currentAngle  = findAngle();
    int Req_Pulse = angleToPulse(ReqAngle);
    while (rev_check != Req_Pulse){
        //printf("rev: %d\n",rev_check);
    }
    //printf("rev: %d\n",rev_check);
    printf("Finished setAngle\n");
    control.setTarget(0);
    control.run();
}

int MyAngle::angleToPulse(double requiredAngle) {
    const int totalPulses = 224;
    const int totalDegrees = 360;
    const float degreesPerPulse = static_cast<float>(totalDegrees) / totalPulses;

    // Calculate the target pulse for the required angle
    double targetPulse = requiredAngle / degreesPerPulse;

    // Round to nearest pulse
    int closestPulse = std::round(targetPulse);

    return closestPulse;
}

double MyAngle::getAngle(){
    double angle = findAngle();
    return angle;
}