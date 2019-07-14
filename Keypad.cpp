/*  Matrix keypad library for Arduino.
    Copyright (C) 2019 Ben Sorge

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

#include <Keypad.h>

// constructor: import instance specific data
Keypad::Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols) {
	keymap = userKeymap;
	rowPins = row;
	columnPins = col;
	rowCount = numRows;
	columnCount = numCols;

	lastKey = NO_KEY;
}

//return the first pressed key it can find. if it can't, return NO_KEY
char Keypad::getKey(void) {
	int col = -1; //-1 == no index was found
	int row = -1;
	
	//set up messurement on column pins
	for (byte i = 0; i < rowCount; i++) pinMode(rowPins[i], OUTPUT);
	for (byte i = 0; i < rowCount; i++) digitalWrite(rowPins[i], LOW);
	for (byte i = 0; i < columnCount; i++) pinMode(columnPins[i], INPUT_PULLUP);
	
	//messure on column pins
	for (byte i = 0; i < columnCount; i++) {
		if (digitalRead(columnPins[i]) == LOW) {
			col = i;
			i = columnCount;
		}
	}
  
	if (col != -1) {
		//set up reverse messurement to find matching row pin
		pinMode(columnPins[col], OUTPUT);
		digitalWrite(columnPins[col], LOW);
		for (byte i = 0; i < rowCount; i++) pinMode(rowPins[i], INPUT_PULLUP);
		
		//messure on row pins
		for (byte i = 0; i < rowCount; i++) {
			if (digitalRead(rowPins[i]) == LOW) {
				row = i;
				i = rowCount;
			}
		}
	}
	
	//if a key was found, return corresponding character
	if (col != -1 && row != -1) return keymap[row * columnCount + col];
	else return NO_KEY;
}

//returns a key only one time, until it becomes released and pressed again
char Keypad::getNewKey(bool noDebounceDelay = false) {
	static unsigned long lastRequest = 0;


	if (noDebounceDelay == false) {
		//check if debounce time has already passed; if not, wait for it
		//make sure it still works, even if millis() overflows (after about 50 days)
		while (millis() - lastRequest < debounceDelay && millis() >= lastRequest);
	}

	//get new reading
	char newKey = getKey();

	//save time for next function call
	lastRequest = millis();

	if (newKey == lastKey) { //no change
		return NO_KEY;
	}
	else { //key changed
		lastKey = newKey;
		return newKey;
	}
}

//setup meassurement on row pins
//set interrupts to falling edge detection on column pins to detect KeyDown-event
void Keypad::prepIrOnRowPins(void) {
	for (byte i = 0; i < columnCount; i++) pinMode(columnPins[i], OUTPUT);
	for (byte i = 0; i < columnCount; i++) digitalWrite(columnPins[i], LOW);
	for (byte i = 0; i < rowCount; i++) pinMode(rowPins[i], INPUT_PULLUP);
}

//setup meassurement on column pins
//set interrupts to falling edge detection on row pins to detect KeyDown-event
void Keypad::prepIrOnColumnPins(void) {
	for (byte i = 0; i < rowCount; i++) pinMode(rowPins[i], OUTPUT);
	for (byte i = 0; i < rowCount; i++) digitalWrite(rowPins[i], LOW);
	for (byte i = 0; i < columnCount; i++) pinMode(columnPins[i], INPUT_PULLUP);
}

void Keypad::setDebounceDelay(byte value) {
	debounceDelay = value;
}

byte Keypad::getDebounceDelay(void) {
	return debounceDelay;
}
