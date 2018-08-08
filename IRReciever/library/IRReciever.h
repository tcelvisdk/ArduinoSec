#include <IRremote.h>
#define CHMINUS 0xFFA25D
#define CH      0xFF629D
#define CHPLUS  0xFFE21D

#define PREV    0xFF22DD
#define NEXT    0xFF02FD
#define PAUSE   0xFFC23D

#define MINUS   0xFFE01F
#define PLUS    0xFFA857
#define EQ      0xFF906F

#define ZERO    0xFF6897
#define ADD100  0xFF9867
#define ADD200  0xFFB04F

#define ONE     0xFF30CF
#define TWO     0xFF18E7
#define THREE   0xFF7A85

#define FOUR    0xFF10EF
#define FIVE    0xFF38C7
#define SIX     0xFF5AA5

#define SEVEN   0xFF42BD
#define EIGHT   0xFF4AB5
#define NINE    0xFF52AD

decode_results results;
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);

bool isNumber(unsigned long value)
{
	switch (value)
	{
	case CHMINUS:   //FFA25D
		return false;
		break;
	case CH:      //FF629D
		return false;
		break;
	case CHPLUS:    //FFE21D
		return false;
		break;

	case PREV:      //FF22DD
		return false;
		break;
	case NEXT:      //FF02FD

		break;
	case PAUSE:     //FFC23D
		return false;
		break;

	case MINUS:     //FFE01F
		return false;
		break;
	case PLUS:      //FFA857
		return false;
		break;
	case EQ:      //FF906F
		return false;
		break;

	case ZERO:      //FF6897
		return true;
		break;
	case ADD100:    //FF9867
		return false;
		break;
	case ADD200:    //FFB04F
		return false;
		break;

	case ONE:     //FF30CF
		return true;
		break;
	case TWO:     //FF18E7
		return true;
		break;
	case THREE:     //FF7A85
		return true;
		break;

	case FOUR:      //FF10EF
		return true;
		break;
	case FIVE:      //FF38C7
		return true;
		break;
	case SIX:     //FF5AA5
		return true;
	case SEVEN:     //FF42BD
		return true;
		break;
	case EIGHT:     //FF4AB5
		return true;
		break;
	case NINE:      //FF52AD
		return true;
		break;
	default:
		return false;
		break;
	}
}
int getNumber(unsigned long value)
{
	switch (value)
	{
	case ZERO:      //FF6897
		return 0;
		break;
	case ONE:     //FF30CF
		return 1;
		break;
	case TWO:     //FF18E7
		return 2;
		break;
	case THREE:     //FF7A85
		return 3;
		break;

	case FOUR:      //FF10EF
		return 4;
		break;
	case FIVE:      //FF38C7
		return 5;
		break;
	case SIX:     //FF5AA5
		return 6;
	case SEVEN:     //FF42BD
		return 7;
		break;
	case EIGHT:     //FF4AB5
		return 8;
		break;
	case NINE:      //FF52AD
		return 9;
		break;
	default:
		return 0;
		break;
	}
}
void dummy(int x)
{
	;
}

int ReadIRNumber(int digits, void(*f)(int) = dummy)
{
	int toBeReturned = 0;
	int returnDigit = 0;
	int maxNumber = (digits > 4) ? 32767 : ((10 * (digits + 1)) - 1);
	unsigned long valueRead;
	bool keepLooping = true;
	int theNumber;
	while (keepLooping)
	{
		//Serial.println("In loop");

		if (irrecv.decode(&results))
		{
			Serial.println("something");
			valueRead = results.value;
			irrecv.resume();
			if (isNumber(valueRead))
			{
				theNumber = getNumber(valueRead);
				(*f)(theNumber);
				//delay(1000);
				if ((toBeReturned != 0) & (toBeReturned < 3276)
					| (toBeReturned == 3276) & (theNumber < 7))
				{
					toBeReturned = toBeReturned * 10;
					toBeReturned = toBeReturned + theNumber;
				}
				else if (toBeReturned == 0)
				{
					toBeReturned = toBeReturned + theNumber;
				}
			}

			else if (valueRead == PAUSE)
			{
				keepLooping = false;
			}

		}
	}

	int deciNumber = (int)pow(10, digits);
	int intDividede = toBeReturned / deciNumber;
	int returnValue = toBeReturned - (intDividede * deciNumber);
	return returnValue;
}

void initializeIR()
{
	irrecv.enableIRIn();
	irrecv.blink13(true);
}
