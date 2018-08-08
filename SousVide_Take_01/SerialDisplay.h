#pragma once
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class SerialDisplay
{

public:
	SerialDisplay();
	virtual ~SerialDisplay();

};



SerialDisplay::SerialDisplay()
{
	lcd.begin(16, 2); // set up the LCD's number of columns and rows:
	lcd.backlight();  // power on backlight
}


SerialDisplay::~SerialDisplay()
{
}
