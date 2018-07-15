#include "library\IRReciever.h"


void writeNumber(int noIn)
{
  Serial.print("Entered ");
  Serial.println(noIn);
}


void setup()
{
  Serial.begin(9600);
}

void loop() {
  
  Serial.println(ReadIRNumber(3, writeNumber));
  //Serial.println(ReadIRNumber(3));
  //  if (irrecv.decode(&results)) {
  //    Serial.println(results.value, HEX);
  //    irrecv.resume();
}


