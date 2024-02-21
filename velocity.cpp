#include "velocity.h"

volatile long prevTime = 0;
volatile int positionPrev = 0;

float calc_velocity(){
    // Compute velocity
  long currT = time_us_32();
  float deltaT = ((float) (currT-prevTime));
  float velocity = ((position - positionPrev)*(1.0e6))/deltaT;
  //Gearbox Correction
  velocity = velocity/19.2;
  positionPrev = position;
  prevTime = currT;
  return velocity;
}