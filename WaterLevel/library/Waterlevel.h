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