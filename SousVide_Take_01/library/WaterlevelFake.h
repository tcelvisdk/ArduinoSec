int waterlevelGPIO;
void initializeWaterlevel(int GPIO)
{
	waterlevelGPIO = GPIO;
}

int readWaterlevel(int GPIO)
{
	return 3
}

bool WaterCovered(int GPIO)
{
	if (WaterLevel(GPIO) > 9)
		return true;
	else
		return false;
}