//PoE Lab 1: Bike light
//Annie Kroo, Adam Selker, 2017-09
//Lights, flashes, and pulses a number of LED's, using a button to 
// change mode and a potentiometer to change speed.  

static int ledPins[] = {3, 5, 6, 9, 10, 11}; //These are all PWM pins
static int ledCount = 6;
static int buttonPin = 2;
static int potPin = A0; //The wiper; should vary from 0 to 1024
static unsigned int bounceDelay = 16382; //microseconds -- 16383 max
static unsigned int bounceMult = 5; //Multiplier for more delay
static float speedMult = 5; 

volatile int mode = 0;
//Modes: Off, On, Dim, Flash, Pulse, Scan, Pulse Scan, 

unsigned long int lastTime;
int timer = 0;

void switchMode() { //This runs whenever the button pin goes high

  noInterrupts(); //disable interrupts  while in an interrupt
  //Serial.print(mode);
  mode++;
  if (mode > 6) mode = 0; //So the modes loop
  for (int i = 0; i < bounceMult; i++)
    delayMicroseconds(bounceDelay); //Debouncing
  while (digitalRead(buttonPin) == HIGH) 
    delayMicroseconds(1000); //Wait until the button is released
  for (int i = 0; i < bounceMult; i++)
    delayMicroseconds(bounceDelay); //Debouncing
  interrupts();

}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ledCount; i++) 
    pinMode(ledPins[i], OUTPUT); //Set the LED pins to outputs
  pinMode(potPin, INPUT); //And set the pot and button pins to inputs
  pinMode(buttonPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), switchMode, RISING); 
    //Interrupt on the button pin to switch modes

  lastTime = millis(); //Initialize the timer thing

  //Serial.begin(9600);
}

void loop() {
  
  for (int i = 0; i < ledCount; i++) { //Once per pin
    switch (mode) {
      case 0: //Off
        digitalWrite(ledPins[i], LOW);
        break;
      case 1: //On
        digitalWrite(ledPins[i], HIGH);
        break;
      case 2: //Dim
        analogWrite(ledPins[i], 127); //Half brightness
        break;
      case 3: //Flash
        if ((timer % 1000) > 500) digitalWrite(ledPins[i], HIGH);
        else digitalWrite(ledPins[i], LOW);
        break;
      case 4: //Pulse
        analogWrite(ledPins[i], \
          ((sin(float(timer) / 1000.0 * 2.0*PI)) + 1) / 2 * 256);
        break;
      case 5: //Scan
        if (((timer + (1000 / ledCount)*i) % 1000)>(1000 - 1000/ledCount)) 
          digitalWrite(ledPins[i], HIGH);
        else digitalWrite(ledPins[i], LOW);
        break;
      case 6: //Pulse Scan
        analogWrite(ledPins[i], \
          ((sin(float(timer+(1000/ledCount*i)) / 1000.0*2.0*PI))+1) / 2*256);
      default:
        //Do nothing -- should never happen, leave LEDs as fallback
        break;

    } //End swtich
  } //End for

  timer += int((millis()-lastTime) * \
    (float(analogRead(potPin)) * speedMult/1024.0));
    //Adjust the timer based on the pot pin and the last loop time
  timer = timer % 1000; //Everything is mod 1000, this prevents overflow etc.
  lastTime = millis(); //So we'll know how long the next loop takes

  //Serial.println(lastTime);

}

