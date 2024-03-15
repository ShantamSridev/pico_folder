    #ifndef ANGLE_H
    #define ANGLE_H

    #include "pindefs.h"
    #include <cstdio>
    #include <cmath>
    #include "pico/stdlib.h"
    #include "encoder.h"
    #include "pid.h"

    class MyPID;

    class MyAngle{
    public:
        MyAngle();

        void runAngleInit(MyPID& pid);  // Accept MyPID by reference
        void setAngle(double angle, MyPID& pid);  // Accept MyPID by reference
        double getAngle();

    private:
        bool flag;
        int angleToPulse(double);
        double findAngle();
    };
    #endif