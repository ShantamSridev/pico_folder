#include "pindefs.h"
#include "modules/MiniPID/MiniPID.h"

class MyPID{
public:
	MyPID(double, double, double);

    void setTarget(double);
    double getOutput(double);

	void setPID(double, double, double);
	void setMaxIOutput(double);
	void setOutputLimits(double,double);
	void setDirection(bool);
	void setSetpoint(double);
	void reset();
	void setOutputRampRate(double);
	void setSetpointRange(double);
	void setOutputFilter(double);

private:
    MiniPID PID;

	void init();
    double mapValue(double, double, double, double, double);

    double maxPWMOutput;
    double minPWMOutput;
	double maxOutput; 
	double minOutput;
    
	double P;
	double I;
	double D;
	double F;

	double maxIOutput;
	double maxError;
	double errorSum;

	double setpoint;

	double lastActual;

	bool firstRun;
	bool reversed;

	double outputRampRate;
	double lastOutput;

	double outputFilter;

	double setpointRange;

};