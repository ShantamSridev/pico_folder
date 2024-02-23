    #ifndef ANGLE_H
    #define ANGLE_H

    #include "pindefs.h"
    #include <cstdio>
    #include <cmath>
    #include "pico/stdlib.h"
    #include "encoder.h"
    #include "pid.h"

    class angle{
    public:
        angle();

        void runAngle(MyPID);
        void setAngle(double, MyPID);
        double getAngle();

    private:
        bool flag;
        int angleToClosestPulse(double);
        double findAngle();
    };
    #endif