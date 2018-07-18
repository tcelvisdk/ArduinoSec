
#include "library\SerialDisplay.h"
#include "library\Persist.h"

const int bClear = 2;
const int bRead = 3;
const int bWrite = 4;

int addr = 0;
String val;
String _constData = "Data: ";
String _constNowStoring = "Now storing: ";
int bClearState;
int bReadState;
int bWriteState;

void setup()
{
  Serial.begin(9600);
  DisplayInitialize();
  pinMode(bClear, INPUT);
  pinMode(bRead, INPUT);
  pinMode(bWrite, INPUT);
  WriteString("Ready");
  delay(5000);
}

void loop()
{
  bClearState = digitalRead(bClear);
  bReadState = digitalRead(bRead);
  bWriteState = digitalRead(bWrite);

  if  ( bClearState == HIGH)
  {
    WriteString("Now clearing data");
    delay(1000);
    eepromClear();
    WriteString("Data cleared");
  }
  else
  {
    if  ( bReadState == HIGH)
    {
      WriteString("Now reading data");
      delay(1000);
      String dataIn = eepromReadString(0);
      WriteString("Data read: " + dataIn);
    }
    else
    {
      if  ( bWriteState == HIGH)
      {
        String inputData = Serial.readString();

        WriteString(_constNowStoring + inputData);
        eepromWriteString(addr, inputData);
        delay(1000);
        WriteString("Data stored");

      }
    }
  }
}
