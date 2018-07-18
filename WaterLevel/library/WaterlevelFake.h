int WaterLevel(int GPIO)
{
	int fromThingy = analogRead(GPIO);
	return fromThingy/ 66;
}

bool WaterCovered(int GPIO)
{
	if (WaterLevel(GPIO) > 400)
		return true;
	else
		return false;
}