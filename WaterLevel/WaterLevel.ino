int WATERSENSOR = A0;
void setup()
{
 Serial.begin(9600);
}
 int WaterLevel(int GPIO)
 {
  return analogRead(GPIO);
 }

 bool WaterCovered(int GPIO)
 {
  if (WaterLevel(GPIO) > 400)
      return true;
  else
      return false;
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
