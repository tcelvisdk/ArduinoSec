
#include "library\SerialDisplay.h"
#include "library\Persist.h"
#include "TimerOne.h"

// Const IO
static int redPort = 3;
static  int greenPort = 5;
static  int bluePort = 6;
static  int btPressPort = 13;
static int stateButton = 2;

// control vars
int programState = 1;
int bStateState;
bool lastReadHigh = false;
bool doStuff;
int currentDisplay = 0;
int showCount;
int showDelay = 5;
int operationDisplays[] = { 0, 1, 2 };

// function vars

bool heating = false;
int SelectedTemp;
int SelectedDuration;
int StartHour;
int StartMinutes;
int StartDD;
int StartMO;
int StartHHYY;

int DoneDuration;
int DoneHour;
int DoneMinutes;

int CurrentTemp;
int CurrentHour;
int CurrentMinutes;
int CurrentDD;
int CurrentMO;
int CurrentHHYY;

char displays[15][33];

void SousVideDisplayUpdate(int displayNo, int p1, int p2 = 0, int p3 = 0, int p4 = 0, int p5 = 0, char p6 = "")
{
  //Because of a complier error - or something I just cannot see - the following has been placed outside the switch
  if (displayNo = 0)
    sprintf(displays[0], "Temperatur %d3%c  Valgt       %d2  ", p1, p2);
  if (displayNo = 1)
    sprintf(displays[1], "Faerdig kl %d2:%d2Klokken er %d2:%d2", p1, p2, p3, p4);

  switch (displayNo)
  {
    case 0:
      //		sprintf(displays[0], "Temperatur %d3%c  Valgt       %d2  ", p1, p2);
      break;
    case 1:
      //		sprintf(displays[1], "Faerdig kl %d2:%d2Klokken er %d2:%d2", p1, p2, p3, p4);
      break;
    case 2:
      sprintf(displays[2], "Valgt   %d4 minTilbage %d4 min", p1, p2);
      break;
    case 3:      // The prepare display 1
      sprintf(displays[3], "Vælg temperatur             %d2  ", p1);
      break;
    case 4:      // The prepare display 2
      sprintf(displays[4], "Antal min. %d4  Færdig kl %d2:%d2 ", p1, p2, p3);
      break;
    case 5:       // The config display
      sprintf(displays[5], "Indstil ur      %d2:%d2 %d2:%d2 %d4 ", p1, p2, p3, p4, p5);
      break;
    case 6:      // The error display
      strcpy(displays[6], "Fejl: Kontroller      vandstand ");
      break;
    default:
      break;
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
void DisplayRoutine()
{ Serial.print( "in Print: programState ");
  Serial.println( programState);

  if ((programState == 2) & (showCount < showDelay))
  {
    Serial.print( "in Print: showCount ");
    Serial.println( showCount);
    Serial.print( "in Print: currentDisplay ");
    Serial.print( currentDisplay);
    int dispPtr = operationDisplays[currentDisplay];
    Serial.print( " dispPtr ");
    Serial.print( dispPtr);
    String toDisplay(displays[dispPtr]);
    Serial.print( "in Print: toDisplay ");
    Serial.println(toDisplay);
    WriteString(toDisplay);
    showCount++;
  }
  if (showCount == showDelay)
  {
    showCount = 0;
    currentDisplay++;
    if (currentDisplay > (int)(sizeof(operationDisplays) / sizeof(int)))
      currentDisplay = 0;
  }
  Serial.print( "end Print: showCount ");
  Serial.println( showCount);
  Serial.print( " currentDisplay ");
  Serial.println( currentDisplay);
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
  //
  //	//Set up display
  DisplayInitialize();
  //	delay(500);
  //	//Setup "screens"
  for (size_t i = 0; i < 7; i++)
  {
    SousVideDisplayUpdate(i, 0);
  }
  //	WriteString("Hu hej hvor det går");
  //
  //	//Setup Timer
  //// Timer1.initialize(10000000); // set a timer of length 100000 microseconds
  ////
  Timer1.attachInterrupt(DisplayRoutine); // attach the service routine here
  //
  //	//Set up remote control
  //	//Set up thermometer
  //	//Set up relay
  //	//Set up pump
  //	//Set up time
  //	//Set up alarm
  //	//Set up buttons  //config, perpare
  //	setGreen();
}
void loop() {
  // State control
  bStateState = digitalRead(stateButton);
  //  Serial.println(bStateState, HEX);
  if (bStateState == HIGH)
    digitalWrite(btPressPort, HIGH);
  else
    digitalWrite(btPressPort, LOW);

  if (!lastReadHigh & bStateState == HIGH)
  {
    Serial.print("In action ");
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
    Serial.print("programState ");
    Serial.println(programState);

  }
  else if (bStateState == LOW & lastReadHigh)
  {
    lastReadHigh = false;
  }

  if (doStuff)
  {
    switch (programState)
    {
      case 1:  // Prepare
        setRed();
        break;
      case 2:  // Operation
        setGreen();
        break;
      case 3: //
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
