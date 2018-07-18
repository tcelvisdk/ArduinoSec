// include the library code:
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//#include "library\helpfunctions.h"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.
String displayBuffer;
void DisplayInitialize()
{
	lcd.begin(16, 2); // set up the LCD's number of columns and rows:
	lcd.backlight();  // power on backlight
}

void ClearDisplayBuffer()
{
	displayBuffer;
	
}

void WriteLineOne(String text)
{
#ifdef TESTMODE
	String here = "in One ";
	here.concat(text);
	Serial.println(here);
#endif
	String outText = text;
	if (outText.length() < 16)
		outText.concat("                ");
	lcd.setCursor(0, 0); //Second line
	lcd.print(outText);
}

void WriteLineTwo(String text)
{
#ifdef TESTMODE
	String here = "in Two ";
	here.concat(text);
	Serial.println(here);
#endif

	String outText = text;
	if (outText.length() < 16)
		outText.concat("                ");
	lcd.setCursor(0, 1); //Second line
	lcd.print(outText);
}
void WriteDisplayBuffer(int scroll)
{
	int start1 = 0;
	int end1 = 0;
	int start2 = 0;
	int end2 = 0;

	String b;
	lcd.setCursor(0, 0);
	int messageStartPos = 0;
	int messageLenght = displayBuffer.length();
	if (messageLenght > 16)
	{
		start1 = 0;
		end1 = 16;
		start2 = 16;
		if (messageLenght > 32)
			end2 = 32;
		else
			end2 = messageLenght;

		WriteLineOne(displayBuffer.substring(start1, end1));
		WriteLineTwo(displayBuffer.substring(start2, end2));

		if (messageLenght > end2)
		{
			bool endOfMessage = false;

			while (!endOfMessage)
			{
				delay(250);

				start1 += scroll;
				end1 += scroll;
				start2 += scroll;
				end2 += scroll;

				WriteLineOne(displayBuffer.substring(start1, end1));
				if (end1 < messageLenght)
					WriteLineTwo(displayBuffer.substring(start2, end2));
				else
					WriteLineTwo("                ");
				if (end1 > messageLenght)
					endOfMessage = true;
			}
			lcd.clear();
		}
	}
	else
		WriteLineOne(displayBuffer);
	start1 = 0;
	end1 = 0;
	start2 = 0;
	end2 = 0;


	ClearDisplayBuffer();
}

void WriteString(String text)
{
#ifdef TESTMODE
	String here = "in WriteString ";
	here.concat(text);
	Serial.println(here);
	String outBuffer = "displayBuffer: ";
	here.concat(displayBuffer);
	Serial.println(outBuffer);
#endif
	lcd.clear();
	ClearDisplayBuffer();
	displayBuffer = text;
	WriteDisplayBuffer(1);
	//lcd.write(text);
}

