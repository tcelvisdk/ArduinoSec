#include "library\timer.h"
#include "library\SerialDisplay.h"

// control vars
int programState = 2;
int bStateState;
bool lastReadHigh = false;
bool doStuff = true;
bool displayActive = false;
int currentDisplay = 0;
int showCount = 0;
int showDelay = 5;
int operationDisplays[] = { 0, 1, 2 };
bool DisplayStuff = false;

char displays[15][33];

//String nat(char nCha)
//{
//switch (nCha)
//when 'æ':
//
// break;
///*
//  197 Å
//  198 Æ
//  216 Ø
//  229 å
//  230 æ
//  248 ø
//*/
//}
void SousVideDisplayUpdate(int displayNo, int p1, int p2 = 0, int p3 = 0, int p4 = 0, int p5 = 0, char p6 = "")
{
  String formatString;
 
  String aeS('æ');
  switch (displayNo)
  {
    case 0:
      formatString = "Temperatur %3d  Valgt       %2d  ";
      break;
    case 1:
      //                123456789012  345  1234567890123  456
      formatString = "Faerdig kl %02d:%02dKlokken er %02d:%02d";
      break;
    case 2:
      formatString = "Valgt   %4d minTilbage %4d min";
      break;
    case 3:      // The prepare display 1
      formatString = "Vælg temperatur             %2d";
      break;
    case 4:      // The prepare display 2
      formatString = "Antal min. %4d  Færdig kl %02d:%02d ";
      break;
    case 5:       // The config display
      formatString = "Indstil ur      %02d:%02d %02d:%02d %4d ";
      break;
    case 6:      // The error display
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
void DisplayRoutineGo(void*)
{
  DisplayStuff = true;
  addTaskToQueue(&DisplayRoutineGo, NULL, 1000);
}
void DisplayRoutine(void*)
{
  if (DisplayStuff)
  {
    //  Serial.print( "in Print: programState ");
    //  Serial.print( programState);
    //
    //  Serial.print( "| showCount ");
    //  Serial.print( showCount);
    //
    //  Serial.print( " showDelay ");
    //  Serial.println( showDelay);

    //if (!displayActive)
    {
      displayActive = true;
      if ((programState == 2) & (showCount < showDelay))
      {
        //      Serial.print( "in Print: currentDisplay ");
        //      Serial.println ( currentDisplay);
        int dispPtr = operationDisplays[currentDisplay];
        //    Serial.print( " dispPtr ");
        //    Serial.println( dispPtr);
        //    Serial.print( "displays[dispPtr] ");
        //    Serial.print( displays[dispPtr]);

        String toDisplay(displays[dispPtr]);
        Serial.println(toDisplay);

        //    Serial.print( "in Print: toDisplay ");
        //    Serial.println(toDisplay);
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
      //  Serial.print( "end Print: showCount ");
      //  Serial.println( showCount);
      //  Serial.print( " currentDisplay ");
      //  Serial.println( currentDisplay);
    }
    DisplayStuff = false;
  }

}
void tellMeYouLoveMe(void*)
{
  Serial.print("I love you! The time is: ");
  Serial.println(millis());
  addTaskToQueue(&tellMeYouLoveMe, NULL, 5000); // Keep calling this method every 5 seconds just for the heck of it
}

void tellMeYouLoveMeAgain(void*)
{
  Serial.print("I love you more! The time is: ");
  Serial.println(millis());
  addTaskToQueue(&tellMeYouLoveMeAgain, NULL, 5000); // Keep calling this method every 5 seconds just for the heck of it
}

void setup()
{
  Serial.begin(9600);
  //Set up display
  DisplayInitialize();
  //Setup "screens"
  for (size_t i = 0; i < 7; i++)
  {
    SousVideDisplayUpdate(i, 0);
  }
  WriteString("Ready");

  initializeTimer(5, 100); // Setup the task scheduler with a maximum task count of 5 and a tick rate of 10 Hz
  //addTaskToQueue(&tellMeYouLoveMe, NULL, 5000); // Schedule a call to tellMeYouLoveMe() to occur in five seconds
  //addTaskToQueue(&tellMeYouLoveMeAgain, NULL, 5000); // Schedule a call to tellMeYouLoveMe() to occur in five seconds
  addTaskToQueue(&DisplayRoutineGo, NULL, 1000);
}

void loop()
{
  DisplayRoutine(NULL
                );
}
