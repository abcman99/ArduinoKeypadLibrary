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



void setup() {
  Serial.begin(9600);
}

void loop() {
  //get input from the keypad
  //Note that 'getNewKey' returns a key only once. The button must be released to reset it.
  char userInput = kpd.getNewKey();

  //only print to serial, if a key is pressed
  if (userInput != NO_KEY) {
    Serial.println("The key '" + String(userInput) + "' has been pressed.");
  }
}
