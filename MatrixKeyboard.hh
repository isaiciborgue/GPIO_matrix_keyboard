// MatrixKeyboard.hh
/*
 *	A class that creates a simple matrix keyboard 
 * 	using the wiringPi library and the X11 Xtest 
 * 	extension.
 */


#ifndef _MATRIX_KEYBOARD_HH
#define _MATRIX_KEYBOARD_HH

#include <wiringPi.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

typedef unsigned int uInt;
struct Key
{
	uInt rowPin;
	uInt colPin;
	KeySym keysym;
	uInt lastState;
};

static const bool KEY_DOWN = true;
static const bool KEY_UP = false;
static const uInt nRows = 1;
static const uInt nCols = 2;

class MatrixKeyboard
{
private:

	Display * myXDisplay;
	Key keyboard[nRows][nCols];

public:
	MatrixKeyboard();

private:
	void pressKey(KeySym keysym);
	void releaseKey(KeySym keysym);

public:
	void run();
};

#endif // ! _MATRIX_KEYBOARD_HH