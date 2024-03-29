    #ifndef ANGLE_H
    #define ANGLE_H

    #include "pindefs.h"
    #include <cstdio>
    #include <cmath>
    #include "pico/stdlib.h"
    #include "encoder.h"
    #include "pid.h"

    class MyAngle{
    public:
        MyAngle();

        void runAngleInit(MyPID);
        void setAngle(double, MyPID);
        double getAngle();

    private:
        bool flag;
        int angleToPulse(double);
        double findAngle();
    };
    #endif