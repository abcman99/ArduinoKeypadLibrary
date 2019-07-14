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
