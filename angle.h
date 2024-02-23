    #ifndef ANGLE_H
    #define ANGLE_H

    #include "pindefs.h"
    #include <cstdio>
    #include "pico/stdlib.h"
    #include "encoder.h"
    #include "pid.h"

    class angle{
    public:
        angle();

        double findAngle();
        void runAngle(MyPID);
        void setAngle(double, MyPID);

    private:
        bool flag;
    };
    #endif