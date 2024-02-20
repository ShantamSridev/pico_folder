#include "pindefs.h"
#include "modules/MiniPID/MiniPID.h"

class MyPID{
public:
	MyPID(double, double, double);

    void setTarget(double);
    double getOutput(double);
	void setOutputLimits(double,double);
	void setOutputRampRate(double);

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