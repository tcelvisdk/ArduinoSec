#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

 float Celcius=0;
 float Fahrenheit=0;
 void tempsensorSetup()
 { sensors.begin();
 //
 
  }
float 
 
void setup(void)
{
  
  Serial.begin(9600);
  tempsensorSetup();
}

void loop(void)
{ 

  
  Serial.print(" C  ");
  Serial.print(Celcius);
  Serial.print(" F  ");
  Serial.println(Fahrenheit);
  delay(1000);
}



