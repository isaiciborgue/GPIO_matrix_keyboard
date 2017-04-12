#ifndef _MATRIX_KEYBOARD_HH
#define _MATRIX_KEYBOARD_HH

#include <wiringPi.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

typedef unsigned int uInt; 

class MatrixKeyboard
{
private:
	Display * myXDisplay;
	vector<uInt> rows;
	vector<uInt> cols;
	vector<KeySym> keys;
	vector<bool> lastStates;
	uInt delay;

public:
	MatrixKeyboard(vector<uInt> rows, vector<uInt> cols, vector<KeySym> keys);
	void run();

private:
	void pressKey(KeySym keysym);
	void releaseKey(KeySym keysym);


};

#endif // ! _MATRIX_KEYBOARD_HH
