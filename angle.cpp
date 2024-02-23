#include "angle.h"

angle::angle(){
    flag = true;
}

double angle::findAngle(){
    return rev_check*0.6222222222;
}

void angle::runAngle(MyPID control){
    printf("Starting runAngle");
        control.setTarget(10);
        control.run();
        while (flag){
          flag = (rev_check == 224 && pulse >= 2) ? false : true;
          printf("rev: %d\n",rev_check);
        }
        printf("Finished runAngle");
        control.setTarget(0);
        control.run();
}

void angle::setAngle(double ReqAngle, MyPID control){
    printf("Starting setAngle");
    control.setTarget(8);
    control.run();
    double currentAngle  = findAngle();
    while (currentAngle != ReqAngle){
          printf("rev: %d\n",rev_check);
    }
    printf("Finished setAngle");
    control.setTarget(0);
    control.run();
}