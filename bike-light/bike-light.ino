static int ledPins[] = {3, 5, 6, 9, 10, 11};
static int ledCount = 6;
static int buttonPin = 2;
static long int bounceDelay = 50000; //microseconds

int mode = 0;
//Modes: Off, On, Dim, Flash, Scan

void switchMode() {

  mode++;
  if (mode > 5) mode = 0;
  delayMicroseconds(bounceDelay); //Debouncing
  while (digitalRead(buttonPin) == HIGH) delayMicroseconds(10000); //Wait until the button is released
  delayMicroseconds(bounceDelay); //Debouncing

}

void setup() {
  for (int i = 0; i < ledCount; i++) pinMode(ledPins[i], OUTPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), switchMode, RISING);
}

void loop() {
  
  for (int i = 0; i < ledCount; i++) {
    switch (mode) {
      case 0:
        digitalWrite(ledPins[i], LOW);
        break;
      case 1:
        digitalWrite(ledPins[i], HIGH);
        break;
      case 2:
        analogWrite(ledPins[i], 127); //Half brightness
        break;
      case 3:
        if ((millis() % 1000) > 500) digitalWrite(ledPins[i], HIGH);
        else digitalWrite(ledPins[i], LOW);
        break;
      case 4:
        analogWrite(ledPins[i], ((sin(float(millis()) / 1000.0 * 2.0*PI)) + 1) / 2 * 256);
        break;
      case 5:
        if (((millis() + (1000 / ledCount)*i) % 1000) > ( 1000 - 1000 / ledCount)) digitalWrite(ledPins[i], HIGH);
        else digitalWrite(ledPins[i], LOW);
        break;
      default:
        //Do nothing
        break;

    } //End swtich
  } //End for

}

