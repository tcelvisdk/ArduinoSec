#include "library\SerialDisplay.h"
#include "library\Clock.h"

void displayTime()
{
  dateTime now = getDateTime("da");
  char timeToViewC[17];
  sprintf(timeToViewC, "Klokken er %02i:%02i:%02i", now.hour, now.minute, now.second);
  Serial.println(timeToViewC);
  char weekToViewC[17];
  const char *dayName = now.dayOfWeek.c_str();
  sprintf(weekToViewC, "Det er %s", dayName);
  WriteLineOne(weekToViewC);
  
  char dateToViewC[17];
  sprintf(dateToViewC, "Dato: %02i.%02i 20%02i", now.day, now.month, now.year);

//  String dateToView = String(dayOfMonth, DEC)
//                      + String(".")
//                      + String(month, DEC)
//                      + String(".")
//                      + String(year, DEC);
  WriteLineTwo(dateToViewC);


}

void setup()
{
  initializeClock();
  Serial.begin(9600);
  DisplayInitialize();
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  dateTime thisIsNow;
  thisIsNow.hour = 8;
  thisIsNow.minute = 5;
  thisIsNow.second = 5;
  thisIsNow.dayOfWeekInt = 2;
  thisIsNow.day = 6;
  thisIsNow.month = 8;
  thisIsNow.year = 18;
  setDateTime(thisIsNow);
  //  setDateTime(00, 35, 21, 4, 11, 07, 18);
}

void loop()
{
  displayTime(); // display the real-time clock data on the Serial Monitor,
  delay(1000); // every second
}
