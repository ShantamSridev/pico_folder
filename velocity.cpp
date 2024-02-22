#include "velocity.h"

volatile long prevTime = 0;
volatile int positionPrev = 0;
volatile double vel = 0;

double calc_velocity(){
    // Compute velocity
  long currT = time_us_32();
  double deltaT = ((double) (currT-prevTime));
  double velocity = ((position - positionPrev)*(1.0e6))/deltaT;
  //Gearbox Correction
  velocity = velocity/19.2;
  positionPrev = position;
  prevTime = currT;
  vel = velocity;
  return velocity;
}