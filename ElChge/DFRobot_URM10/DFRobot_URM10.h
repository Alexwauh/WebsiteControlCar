#ifndef DF_URM10_H
#define DF_URM10_H
#include <Arduino.h>


class DFRobot_URM10
{
  public:

  DFRobot_URM10(){};

  float getDistanceCM(int trigPin, int echoPin);
  float getDistanceIN(int trigPin, int echoPin);

  private:

  uint64_t myPulseIn(uint32_t pin, uint32_t value, long maxDuration = 100000);

};

#endif
