#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68
// Convert normal decimal numbers to binary coded decimal

struct dateTime
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int dayOfWeekInt;
	String dayOfWeek;
	String monthOfYear;
};

byte decToBcd(byte val)
{
	return ((val / 10 * 16) + (val % 10));
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
	return ((val / 16 * 10) + (val % 16));
}
String monthName(int monthNumber, String language = "da")
{
	switch (monthNumber) {
	case 1:
		return "Januar";
		break;
	case 2:
		return "Februar";
		break;
	case 3:
		return "Marts";
		break;
	case 4:
		return "April";
		break;
	case 5:
		return "Maj";
		break;
	case 6:
		return "Juni";
		break;
	case 7:
		return "Juli";
		break;
	case 8:
		return "August";
		break;
	case 9:
		return "September";
		break;
	case 10:
		return "Oktober";
		break;
	case 11:
		return "November";
		break;
	case 12:
		return "December";
		break;
	}

}
String weekDay(int dayNumber, String language = "da")
{
	if (language == "da")
	{
		switch (dayNumber) {
		case 1:
			return "Søndag";
			break;
		case 2:
			return "Mandag";
			break;
		case 3:
			return "Tirsdag";
			break;
		case 4:
			return "Onsdag";
			break;
		case 5:
			return "Torsdag";
			break;
		case 6:
			return "Fredag";
			break;
		case 7:
			return "Lørdag";
			break;
		}
	}
	else if (language == "en")
	{
		switch (dayNumber) {
		case 1:
			return "Sunday";
			break;
		case 2:
			return "Monday";
			break;
		case 3:
			return "Tuesday";
			break;
		case 4:
			return "Wednesday";
			break;
		case 5:
			return "Thursday";
			break;
		case 6:
			return "Friday";
			break;
		case 7:
			return "Saturday";
			break;
		}
	}
	else
	{
		switch (dayNumber) {
		case 1:
			return "Sunday";
			break;
		case 2:
			return "Monday";
			break;
		case 3:
			return "Tuesday";
			break;
		case 4:
			return "Wednesday";
			break;
		case 5:
			return "Thursday";
			break;
		case 6:
			return "Friday";
			break;
		case 7:
			return "Saturday";
			break;
		}
	}
}


void setDateTimeB(byte second, byte minute, byte hour, byte dayOfWeek, byte
	dayOfMonth, byte month, byte year)
{
	// sets time and date data to DS3231
	Wire.beginTransmission(DS3231_I2C_ADDRESS);
	Wire.write(0); // set next input to start at the seconds register
	Wire.write(decToBcd(second)); // set seconds
	Wire.write(decToBcd(minute)); // set minutes
	Wire.write(decToBcd(hour)); // set hours
	Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
	Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
	Wire.write(decToBcd(month)); // set month
	Wire.write(decToBcd(year)); // set year (0 to 99)
	Wire.endTransmission();
}

void getDateTimeB(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
	Wire.beginTransmission(DS3231_I2C_ADDRESS);
	Wire.write(0); // set DS3231 register pointer to 00h
	Wire.endTransmission();
	Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
	// request seven bytes of data from DS3231 starting from register 00h
	*second = bcdToDec(Wire.read() & 0x7f);
	*minute = bcdToDec(Wire.read());
	*hour = bcdToDec(Wire.read() & 0x3f);
	*dayOfWeek = bcdToDec(Wire.read());
	*dayOfMonth = bcdToDec(Wire.read());
	*month = bcdToDec(Wire.read());
	*year = bcdToDec(Wire.read());
}

void initializeClock()
{
	Wire.begin();
}
void setDateTime(dateTime inputTime)
{
	byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

	year = (byte)inputTime.year;
	month = (byte)inputTime.month;
	dayOfMonth = (byte)inputTime.day;
	hour = (byte)inputTime.hour;
	minute = (byte)inputTime.minute;
	second = (byte)inputTime.second;
	dayOfWeek = (byte)inputTime.dayOfWeekInt;

	setDateTimeB(second, minute, hour, dayOfWeek, dayOfMonth, month, year);


}

dateTime getDateTime(String language = "da")
{
	dateTime returnTime; // = new dateTime();

						 //String timeToView;
	byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
	// retrieve data from DS3231
	getDateTimeB(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

	returnTime.year = (int)year;
	returnTime.month = (int)month;
	returnTime.day = (int)dayOfMonth;
	returnTime.hour = (int)hour;
	returnTime.minute = (int)minute;
	returnTime.second = (int)second;
	returnTime.dayOfWeekInt = (int)dayOfWeek;
	returnTime.dayOfWeek = weekDay(returnTime.dayOfWeekInt, language).c_str();
	returnTime.monthOfYear = monthName(returnTime.month, language).c_str();

	return returnTime;

}