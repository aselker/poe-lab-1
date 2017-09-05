static int ledPins[] = {3, 5, 6, 9, 10, 11};
static int ledCount = 6;
static int buttonPin = 2;
static int potPin = A0;
static long int bounceDelay = 50000; //microseconds
static float speedMult = 5;

int mode = 0;
//Modes: Off, On, Dim, Flash, Scan

unsigned long int lastTime;
int timer = 0;

void switchMode() {

  noInterrupts();
  mode++;
  if (mode > 6) mode = 0;
  delayMicroseconds(bounceDelay); //Debouncing
  while (digitalRead(buttonPin) == HIGH) delayMicroseconds(10000); //Wait until the button is released
  delayMicroseconds(bounceDelay); //Debouncing
  interrupts();

}

void setup() {
  for (int i = 0; i < ledCount; i++) pinMode(ledPins[i], OUTPUT);
  pinMode(potPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), switchMode, RISING);

  lastTime = millis();

  Serial.begin(9600);
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
        if ((timer % 1000) > 500) digitalWrite(ledPins[i], HIGH);
        else digitalWrite(ledPins[i], LOW);
        break;
      case 4:
        analogWrite(ledPins[i], ((sin(float(timer) / 1000.0 * 2.0*PI)) + 1) / 2 * 256);
        break;
      case 5:
        if (((timer + (1000 / ledCount)*i) % 1000) > ( 1000 - 1000 / ledCount)) digitalWrite(ledPins[i], HIGH);
        else digitalWrite(ledPins[i], LOW);
        break;
      case 6:
        analogWrite(ledPins[i], ((sin(float(timer + (1000 / ledCount*i)) / 1000.0 * 2.0*PI)) + 1) / 2 * 256);
      default:
        //Do nothing
        break;

    } //End swtich
  } //End for

  timer += int( (millis() - lastTime) * (float(analogRead(potPin)) * speedMult / 1024.0) );
  timer = timer % 1000;
  lastTime = millis();

  Serial.println(lastTime);

}

