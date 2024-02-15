#include "pindefs.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/timer.h"


float calc_velocity(int pos, long& prevT, int& posPrev){
    // Compute velocity
  long currT = time_us_32();
  float deltaT = ((float) (currT-prevT));
  float velocity = ((pos - posPrev)*(1.0e6))/deltaT;
  //Gearbox Correction
  velocity = velocity/19.2;
  posPrev = pos;
  prevT = currT;
  return velocity;
}
