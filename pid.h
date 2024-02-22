#include "pindefs.h"
#include "modules/MiniPID/MiniPID.h"
#include "velocity.h"
#include "pwm.h"
#include "encoder.h"

class MyPID{
public:
	MyPID(double, double, double);

    void setTarget(double);
    double getOutput(double);
	void setOutputLimits(double,double);
	void setOutputRampRate(double);
	void run();

private:
    MiniPID PID;

	void init();
    double mapValue(double, double, double, double, double);

    double maxPWMOutput;
    double minPWMOutput;
	double maxOutput; 
	double minOutput;

	double velocityOutput;
	double PWMOutput;
	double outputRampRate;
};