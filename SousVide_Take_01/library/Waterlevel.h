int waterlevelGPIO;
void initializeWaterlevel(int GPIO)
{
	waterlevelGPIO = GPIO;
}

int ReadWaterlevel(int GPIO)
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