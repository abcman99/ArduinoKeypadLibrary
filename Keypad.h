#ifndef KEYPAD_H
#define KEYPAD_H

#include "Arduino.h"

#define NO_KEY 0

class Keypad {
public:
	Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols);

	char getKey(void);
	char getNewKey(bool noDebounceDelay = false);
	void prepIrOnRowPins(void);
	void prepIrOnColumnPins(void);

	void setDebounceDelay(byte value);
	byte getDebounceDelay(void);

private:
	char *keymap;
    byte *rowPins;
    byte *columnPins;
	byte rowCount;
	byte columnCount;
	char lastKey = NO_KEY;
	byte debounceDelay = 1;
};

#endif