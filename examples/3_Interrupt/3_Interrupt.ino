#include <Keypad.h>

//define keypad size
const byte kpdRowCount = 4;
const byte kpdColCount = 4;

//define hardware pins
byte kpdRowPins[kpdRowCount] = {2, 3, 4, 5};
byte kpdColPins[kpdColCount] = {6, 7, 8, 9};

//define coresponding characters (keypad layout)
char kpdKeys[kpdRowCount][kpdColCount] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//constructor kpd
Keypad kpd((char*) kpdKeys, kpdRowPins, kpdColPins, kpdRowCount, kpdColCount);

//variables and constants
char lastUserInput = NO_KEY;



void enableInterruptKpd(void) {
  //this function sets all necessary pins to allow you detecting key presses via interrupts on the column pins
  //the alternative would be prepIrOnRowPins(), which does the same thing just with the row pins
  //see the usage.txt file for further information
  kpd.prepIrOnColumnPins();
  
  //enable interrupt for 4th column pin -> interrupt is triggered, when key A, B, C or D is pressed
  attachInterrupt(digitalPinToInterrupt(kpdColPins[3]), ISR_kpdKeyDown, FALLING);
}

void ISR_kpdKeyDown(void) {
  //determine which key triggered the interrupt - pass it over to loop() via lastUserInput
  //WARNING: If you decide to use getNewKey() instead make sure to set the optional parameter noDebounceDelay to true!
  //getNewKey() uses millis(), which does not work on interrupts and therefor might trap your programm in an infinit loop.
  lastUserInput = kpd.getKey();

  //due to bouncing, there is a chance of reading 'NO_KEY' -> ignore that and try again
  if (lastUserInput != NO_KEY) {
    //if key was found, stop triggering interrupts
    detachInterrupt(digitalPinToInterrupt(kpdColPins[3]));
  }
}

void setup() {
  Serial.begin(9600);
  enableInterruptKpd();
}

void loop() {
  //if key was pressed, print to serial and reenable interrupt
  if (lastUserInput != NO_KEY) {
    Serial.println("The key '" + String(lastUserInput) + "' has been pressed.");
    enableInterruptKpd();
  }

  //do work that takes a long time
  delay(3000);
}
