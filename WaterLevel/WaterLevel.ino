#include "library\Waterlevel.h"
int WATERSENSOR = A0;
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
