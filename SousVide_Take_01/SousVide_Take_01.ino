#include "library\SerialDisplay.h"
#include "library\Persist.h"
#include "library\Timer.h"
#include "library\Clock.h"
//#include "library\Waterlevel.h"
//#include "library\Temperature.h"
#include "library\WaterlevelFake.h"
#include "library\TemperatureFake.h"

// Const IO
static int redPort = 3;
static  int greenPort = 5;
static  int bluePort = 6;
static  int btPressPort = 13;
static int stateButton = 2;

// control vars
int programState = 2;
int bStateState;
bool lastReadHigh = false;
bool doStuff = true;
int currentDisplay = 0;
int showCount;
int showDelay = 5;
int operationDisplays[] = { 0, 1, 2 };

// function vars

bool heating = false;
bool displayStuff = false;
bool displayActive = true;

bool readClock = false;
bool readWaterlevel = false;
bool readTemperature = false;

int SelectedTemp;
int SelectedDuration;

int startHour;
int startMinutes;
int startDD;
int startMO;
int StartHHYY;

int doneDuration;
int doneHour;
int doneMinutes;

int currentTemp;

dateTime now;

char displays[15][33];

void SousVideDisplayUpdate(int displayNo, int p1, int p2 = 0, int p3 = 0, int p4 = 0, int p5 = 0, char p6 = "")
{
  String formatString;

  switch (displayNo)
  {

    case 0:      // The operations display 1
      formatString = "Temperatur %3d  Valgt       %2d  ";
      break;
    case 1:      // The operations display 2
      //                123456789012  345  1234567890123  456
      formatString = "Faerdig kl %02d:%02dKlokken er %02d:%02d";
      break;
    case 2:      // The operations display 3
      formatString = "Valgt   %4d minTilbage %4d min";
      break;
    case 3:      // The prepare display 1
      formatString = "Vaelg temperatur             %2d";
      break;
    case 4:      // The prepare display 2
      formatString = "Antal min. %4d  Faerdig kl %02d:%02d ";
      break;
    case 5:       // The config display 1
      formatString = "Indstil ur      %02d:%02d %02d.%02d %4d ";
      break;
    case 6:       // The config display 2
      //                       11111111112222222222333
      //              12345678901234567890123456789012
      formatString = "Indstil temp    interval %d  ";
      break;
    case 7:       // The config display 3
      formatString = "Indstil ur      %02d:%02d %02d.%02d %4d ";
      break;
    case 8:      // The error display
      strcpy(displays[displayNo], "Fejl: Kontroller      vandstand ");
      break;
    default:
      break;
  }
  if (displayNo != 6)
    sprintf(displays[displayNo], formatString.c_str(), p1, p2, p3, p4, p5);

  Serial.print("display ");
  Serial.print(displayNo);
  Serial.print(" : ");
  Serial.println(displays[displayNo]);
}


void ReadTemperatureGo(void*)
{
  readTemperature = true;
  addTaskToQueue(&ReadTemperatureGo, NULL, 500);
}

int ReadTemperature(int lastTemperature)
{
  if ( readTemperature)
  {
    readTemperature = false;
    return 5;
  }
  else
    return lastTemperature;
}

void ReadWaterlevelGo(void*)
{
  readWaterlevel = true;
  addTaskToQueue(&ReadWaterlevelGo, NULL, 500);
}

int ReadWaterlevel(int lastWaterlevel)
{
  if ( readWaterlevel)
  {
    readWaterlevel = false;
    return 5;
  }
  else
    return lastWaterlevel;
}

void ReadClockGo(void*)
{
  readClock = true;
  addTaskToQueue(&ReadClockGo, NULL, 1000);
}

dateTime ReadClock(dateTime lastDateTime)
{
  if (readClock)
  {
    readClock = false;
    return getDateTime("da");
  }
  else
    return lastDateTime;
}

void DisplayRoutineGo(void*)
{
  displayStuff = true;
  addTaskToQueue(&DisplayRoutineGo, NULL, 1000);
}

void DisplayRoutine()
{
  if (displayStuff)
  {

    displayActive = true;
    if ((programState == 2) & (showCount < showDelay))
    {
      int dispPtr = operationDisplays[currentDisplay];

      String toDisplay(displays[dispPtr]);
      WriteString(toDisplay);
      showCount++;
    }
    if (showCount == showDelay)
    {
      showCount = 0;
      currentDisplay++;
      if (currentDisplay >= (int)(sizeof(operationDisplays) / sizeof(int)))
        currentDisplay = 0;
    }

    displayStuff = false;
  }
}

void setGreen() {
  analogWrite(redPort, 0);
  analogWrite(greenPort, 100);
  analogWrite(bluePort, 0);
}
void setBlue()
{
  analogWrite(redPort, 0);
  analogWrite(greenPort, 0);
  analogWrite(bluePort, 100);
}
void setRed()
{
  analogWrite(redPort, 100);
  analogWrite(greenPort, 0);
  analogWrite(bluePort, 0);
}

int StateOfProgram()
{
  // State control
  bStateState = digitalRead(stateButton);
  //  Serial.println(bStateState, HEX);
  if (bStateState == HIGH)
    digitalWrite(btPressPort, HIGH);
  else
    digitalWrite(btPressPort, LOW);

  if (!lastReadHigh & bStateState == HIGH)
  {
    //Serial.print("In action ");
    lastReadHigh = true;
    doStuff = true;
    if (programState == 1)  // Prepare Mode
    {
      programState++;
    }
    else if (programState == 2)  // Operation Mode
    {
      programState++;
    }
    else if (programState == 3)  // Configuation Mode
    {
      programState = 1;
    }
    //		Serial.print("programState ");
    //		Serial.println(programState);

  }
  else if (bStateState == LOW & lastReadHigh)
  {
    lastReadHigh = false;
  }

  return programState;
}

void setup()
{
  //	// put your setup code here, to run once:
  Serial.begin(9600);

  //Set up Input and output
  pinMode(stateButton, INPUT);
  digitalWrite(stateButton, LOW);
  pinMode(bluePort, OUTPUT);
  pinMode(greenPort, OUTPUT);
  pinMode(redPort, OUTPUT);
  pinMode(btPressPort, OUTPUT);

  //Set up display
  DisplayInitialize();
  //Setup "screens"
  for (size_t i = 0; i < 7; i++)
  {
    SousVideDisplayUpdate(i, 0);
  }
  WriteString("Ready");

  //Setup Timer
  initializeTimer(5, 100);
  addTaskToQueue(&DisplayRoutineGo, NULL, 1000);

  //Set up remote control
  //Set up Waterlevel
  initializeWaterlevel(5);
  addTaskToQueue(&ReadWaterlevelGo, NULL, 500);
  //Set up thermometer
  initializeThermometer(5, 100);
  addTaskToQueue(&ReadTemperatureGo, NULL, 1000);
  //Set up relay
  //Set up pump
  //Set up time
  initializeClock();
  addTaskToQueue(&ReadClockGo, NULL, 1000);
  //Set up alarm
}
void loop() {

  if (doStuff)
  {
    switch (StateOfProgram())
    {
      case 1:  // Prepare
        setRed();
        break;
      case 2:  // Operation
        setGreen();

        break;
      case 3: // Configuration
        setBlue();
        break;
      default:
        break;
    }
    doStuff = false;
  }
  // If ConfigurationMode
  //  Set new time and date
  //  Set temperatureInterval
  // else
  //  if preparing
  //   Accept final_temperature
  //   Accept time
  //  else

  DisplayRoutine();
  now = ReadClock(now);
  currentTemp = ReadTemperature(currentTemp);
  currentWaterlevel = ReadWaterlevel(currentWaterlevel);
  //	ReadTemperature();


  //SousVideDisplayUpdate(1, 0, 0, CurrentHour, CurrentMinutes);


  //   if HeatMode
  //    if current temp < final_temperature + temperatureInterval
  //      HeatMode = false
  //      Stop pump
  //      Stop heath   //engage relay
  //    else
  //    {
  //      HeatMode = true
  //      Start pump
  //      Start heath   //engage relay
  //    }
  //   else
  //    if current temp < final_temperature - temperatureInterval
  //      HeatMode = true


}

