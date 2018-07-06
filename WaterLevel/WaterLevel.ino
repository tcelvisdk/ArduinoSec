#include "library\Waterlevel.h"
#define WATERSENSOR 0

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(WaterLevel(WATERSENSOR));
  if (WaterCovered(WATERSENSOR))
    Serial.println("TRUE");
  else
    Serial.println("FALSE");
  delay(100);
}
