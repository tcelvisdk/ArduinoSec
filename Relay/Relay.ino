#include "library\Relay.h"                    
#define RELAY  7  

void setup()
{
  Serial.begin(9600);
  RelayInitialize(RELAY);
}

void loop()
{
  RelayOn();            // Turns Relays On

  Serial.println("Light ON");
  delay(5000);                    // Wait 5 seconds

  RelayOff();           // Turns Relay Off

  Serial.println("Light OFF");
  delay(5000);
}
