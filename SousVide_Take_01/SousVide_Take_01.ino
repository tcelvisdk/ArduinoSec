
// Const IO
static int redPort = 9;
static  int greenPort = 10;
static  int bluePort  = 11;
static  int btPressPort  = 13;
static int stateButton = 2;

// control vars
int programState = 1;
int bStateState;
bool lastReadHigh = false;
bool doStuff;
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


//String displays[15];
char displays[15][33];

void SousVideDisplayUpdate(int displayNo, int p1, int p2 = 0, int p3 = 0, int p4 = 0, int p5 = 0, char p6 = "")
{
  switch (displayNo)
  {
    case 0:
      //  0_______________
      //1|Temperatur 999 *|
      //2|Valgt       99  |
      //  ----------------
      //                   "         11111 1 111122222222223 33"
      //                   "12345678901234 5 678901234567890 12"
      sprintf(displays[0], "Temperatur %d3%c  Valgt       %d2  ", p1, p2);
      break;
    case 1:
      //  1_______________
      //1|Faerdig kl HH:MM|
      //2|Klokken er HH:MM|
      //  ----------------
      //                   "         1111 111 1112222222222 33 3"
      //                   "1234567890123 456 7890123456789 01 2"
      sprintf(displays[1], "Faerdig kl %d2:%d2Klokken er %d2:%d2", p1, p2, p3, p4);
      break;
    case 2:
      //  2_______________
      // |Valgt   9999 min|
      // |Tilbage 9999 min|
      //  ----------------
      //                   "         111111111222222222333"
      //                   "123456789023456789012345789012"
      sprintf(displays[2], "Valgt   %d4 minTilbage %d4 min", p1, p2);
      break;
    case 3:
      //
      // The prepare display
      //  0000000001111111
      //  1234567890123456 1234567890123456 //
      //  3_______________
      //1|Vælg temperatur |
      //2|            99  |
      //  ----------------
      //                   "         111111111122222222223 33"
      //                   "123456789012345678901234567890 12"
      sprintf(displays[3], "Vælg temperatur             %d2  ", p1);
      break;
    case 4:
      // After tap
      //  4_______________
      //1|Antal min. 9999 |
      //2|Færdig kl HH:MM |
      //  ----------------
      //
      //                   "         111111111222222222 233 3"
      //                   "123456789012346789012345678 901 2"
      sprintf(displays[4], "Antal min. %d4  Færdig kl %d2:%d2 ", p1, p2, p3 );
      break;
    case 5:
      // The config display
      //  0000000001111111
      //  1234567890123456 1234567890123456 //
      //  5_______________
      //1|Indstil ur      |
      //2|HH:MM DD:MO HHAA|
      //  ----------------
      //                   "         111111111 122 222 222 22333"
      //                   "123456789012345678 901 234 567 89012"
      sprintf(displays[5], "Indstil ur      %d2:%d2 %d2:%d2 %d4 ", p1, p2, p3, p4, p5) ;
      break;
    case 6:
      // The config display
      //  0000000001111111
      //  1234567890123456 1234567890123456 //
      //  5_______________
      //1|Fejl: Kontroller|
      //2|      vandstand |
      //  ----------------
      //                   "         111111111 122 222 222 22333"
      //             "12345678901234567890123456789012"
      strcpy(displays[6], "Fejl: Kontroller      vandstand ");
      break;
    default:
      break;
  }  //

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
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Set up Input and output
  pinMode(stateButton, INPUT);
  digitalWrite(stateButton, LOW);
  pinMode(bluePort, OUTPUT);
  pinMode(greenPort, OUTPUT);
  pinMode(redPort, OUTPUT);
  pinMode(btPressPort, OUTPUT);

  //Set up display
  //Set up remote control
  //Set up thermometer
  //Set up relay
  //Set up pump
  //Set up time
  //Set up alarm
  //Set up buttons  //config, perpare
 setGreen();
}

void loop() {
  // State control
  bStateState = digitalRead(stateButton);
  //  Serial.println(bStateState, HEX);
  if  ( bStateState == HIGH)
    digitalWrite(btPressPort, HIGH);
  else
    digitalWrite(btPressPort, LOW);

  if  ( !lastReadHigh & bStateState == HIGH)
  {
    Serial.print("In action ");
    lastReadHigh = true;
    doStuff = true;
    if (programState == 1)  // Prepare Mode
    { programState++;
    }
    else if (programState == 2)  // Operation Mode
    { programState++;
    }
    else if (programState == 3)  // Configuation Mode
    { programState = 1;
    }
    Serial.print("programState ");
    Serial.println(programState);

  }
  else if  ( bStateState == LOW & lastReadHigh)
  {
    lastReadHigh = false;
  }

  if (doStuff)
  {
    switch ( programState)
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
