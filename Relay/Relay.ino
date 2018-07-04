                       

#define RELAY1  7                        
void setup()

{    


Serial.begin(9600);
  pinMode(RELAY1, OUTPUT);       

}

  void loop()

{

   digitalWrite(RELAY1, 0);           // Turns ON Relays 1
   
   Serial.println("Light ON");
   delay(5000);                       // Wait 5 seconds

   digitalWrite(RELAY1, 1);           // Turns Relay Off
   
   Serial.println("Light OFF");
   delay(5000);
   
}
