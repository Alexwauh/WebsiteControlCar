#include "DFRobot_URM10.h"
#if defined(ESP_PLATFORM)
#include "pins_arduino.h"
#endif

float DFRobot_URM10::getDistanceCM(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  long duration;
  if (digitalRead(echoPin) == 0)
  {
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigPin, LOW);
    duration = myPulseIn(echoPin, HIGH);
  }
  else
  {
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin, LOW);
    duration = myPulseIn(echoPin, LOW);
  }

  duration = duration / 59;
  // if ((duration <=0) || (duration > 500)) return 0;
  delay(10);
  return duration;
}

float DFRobot_URM10::getDistanceIN(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  long duration;
  if (digitalRead(echoPin) == 0)
  {
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigPin, LOW);
    duration = myPulseIn(echoPin, HIGH);
  }
  else
  {
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin, LOW);
    duration = myPulseIn(echoPin, LOW);
  }

  duration = duration / 59;
  // if ((duration <=0) || (duration > 500)) return 0;
  delay(50);
  return duration / 2.54;
}

uint64_t DFRobot_URM10::myPulseIn(uint32_t pin, uint32_t value, long maxDuration)
{
  int pulse = value == HIGH ? 1 : 0;
  uint64_t tick = micros();
  uint64_t maxd = (uint64_t)maxDuration;
  while (digitalRead(pin) != pulse)
  {
    if (micros() - tick > maxd)
      return 0;
  }
  uint64_t start = micros();
  while (digitalRead(pin) == pulse)
  {
    if (micros() - tick > maxd)
      return 0;
  }
  uint64_t end = micros();
  return end - start;
}