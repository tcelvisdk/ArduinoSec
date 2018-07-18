int WaterLevel(int GPIO)
{ 
	int fromThingy = analogRead(GPIO);
	return fromThingy/40;
}

bool WaterCovered(int GPIO)
{
	if (WaterLevel(GPIO) > 9)
		return true;
	else
		return false;
}