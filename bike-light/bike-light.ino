static int ledPins[] = {3, 5, 6, 9, 10, 11};
static int ledCount = 6;
static int buttonPin = 2;
static int bounceDelay = 10000; //10 milliseconds

int mode = 0;
//Modes: Off, On, Dim, Flash, Scan

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
      default:
        //Do nothing
        break;

    } //End swtich

}

void switchMode() {

  mode++;
  if (mode > 2) mode = 0;
  delayMicroseconds(bounceDelay); //Debouncing

}
