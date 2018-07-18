#define TESTMODE

#ifdef TESTMODE
#include "library\WaterlevelFake.h"
#endif

#ifndef TESTMODE
#include "library\WaterlevelFake.h"
#endif

#define WATERSENSOR 0 //Analog 0

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
