#include <EEPROM.h>

const int MAXSTORAGE = 100;

void eepromClear()
{
	for (int i = 0; i < MAXSTORAGE; i++) {
		EEPROM.write(i, 0);
	}
}
void eepromWriteString(int StartPosition, String inputStr)
{
	char *myArray;
	myArray = inputStr.c_str();
	int dataPosition = StartPosition;
	for (int i = StartPosition; ((myArray[i] != '\0') && (i < MAXSTORAGE)); i++) {
		EEPROM.write(i, myArray[i]);
		dataPosition++;
	}
	EEPROM.write(dataPosition, '\0');
}

String eepromReadString(int StartPosition)
{
	//String returnString;
	char myArray[MAXSTORAGE];
	int dataPosition = 0;
	for (int i = StartPosition; i < MAXSTORAGE; i++)
	{
		myArray[dataPosition] = EEPROM.read(i);
		dataPosition++;
	}
	String _returnString(myArray);
	return _returnString;
}