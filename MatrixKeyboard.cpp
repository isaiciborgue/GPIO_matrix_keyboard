#include "MatrixKeyboard.hh"

MatrixKeyboard::MatrixKeyboard(vector<uInt> rows, vector<uInt> cols, vector<KeySym> keys)
{
	// Initializing X Display
	myXDisplay = XOpenDisplay(NULL);
	if (! myXDisplay)
   		cerr << "Couldn't open the X display." << endl;

   	// Initialize WiringPi Library
   	if (wiringPiSetup() < 0)
		cerr << "Couldn't initialize the wiringPi library." << endl;

	this->rows = rows;
	this->cols = cols;
	this->keys = keys;
	for (uInt i = 0; i < this->keys.size(); i++)
		lastStates.push_back(false);

	for (uInt i = 0; i < this->rows.size(); i++)
	{
		pinMode(this->rows[i], OUTPUT);
		digitalWrite(this->rows[i], LOW);
	}

	for (uInt i = 0; i < this->cols.size(); i++)
	{
		pinMode(this->cols[i], INPUT);
		pullUpDnControl(this->cols[i], PUD_DOWN);
	}
	
	delay = 5;
}


void MatrixKeyboard::run()
{
	uInt k = 0;
	
	while (true)
	{
		k = 0;
		for (uInt i = 0; i < rows.size(); i++)
		{
			digitalWrite(rows[i], HIGH);
			sleep_for(milliseconds(delay));

			for (uInt j = 0; j < cols.size(); j++)
			{
				sleep_for(milliseconds(delay));
				if (digitalRead(cols[j]))
				{
					if (! lastStates[k])
					{
						pressKey(keys[k]);
						lastStates[k] = true;
					}

					k++;
				}
				else 
				{
					if (lastStates[k]) 
					{
						releaseKey(keys[k]);
						lastStates[k] = false;
					}

					k++;
				}
			}
			digitalWrite(rows[i], LOW);
		}
	}
}


void MatrixKeyboard::pressKey(KeySym keysym)
{
	KeyCode keycode = 0;
	keycode = XKeysymToKeycode (myXDisplay, keysym);
	if (keycode == 0) 
		return;
	
	XTestGrabControl (myXDisplay, True);
	
	//XTestFakeKeyEvent (myXDisplay, keycode, False, 0);
	XTestFakeKeyEvent (myXDisplay, keycode, True, 0);

	XSync (myXDisplay, False);
	XTestGrabControl (myXDisplay, False);
}


void MatrixKeyboard::releaseKey(KeySym keysym)
{
	KeyCode keycode = 0;
	keycode = XKeysymToKeycode (myXDisplay, keysym);
	if (keycode == 0) 
		return;
	
	XTestGrabControl (myXDisplay, True);
	
	XTestFakeKeyEvent (myXDisplay, keycode, False, 0); 

	XSync (myXDisplay, False);
	XTestGrabControl (myXDisplay, False);
}
