
int sensorPin = A1;    // select the input pin for the potentiometer
int ledPin = 8;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

int get_temperature(int pin) {
  int temperature = analogRead(pin);
  // Calculate the temperature based on the reading and send that value back
  float voltage = temperature * 5.0;
  voltage = voltage / 1024.0;
  return ((voltage - 0.5) * 100);
}

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  Serial.println(get_temperature(sensorPin));
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(1000);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(1000);
}
