#include "MatrixKeyboard.hh"

MatrixKeyboard::MatrixKeyboard()
{
	// Connect to the X server
	myXDisplay = XOpenDisplay(NULL);

   if (! myXDisplay)
   		cerr << "Couldn't open the X display." << endl;

   // Initialize the `wiringPi` library
   	if (wiringPiSetup() == -1)
		cerr << "Couldn't initialize the wiringPi library." << endl;

	keyboard[0][0].rowPin = 12;
	keyboard[0][0].colPin = 13;
	keyboard[0][0].keysym = XK_X;

	keyboard[0][1].rowPin = 12;
	keyboard[0][1].colPin = 14;
	keyboard[0][1].keysym = XK_A;

	for (uInt i = 0; i < nRows; i++)
	{
		pinMode(keyboard[i][0].rowPin, OUTPUT);
		digitalWrite(keyboard[i][0].rowPin, LOW);
	}

	for (uInt j = 0; j < nCols; j++)
	{
		pinMode(keyboard[0][j].colPin, INPUT);
		pullUpDnControl(keyboard[0][j].colPin, PUD_DOWN);
	}

	for (uInt i = 0; i < nRows; i++)
		for (uInt j = 0; j < nCols; j++)
			keyboard[i][j].lastState = KEY_DOWN;
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


void MatrixKeyboard::run()
{
	uInt z = 0;
	while (z < 1000)
	{
		for (uInt i = 0; i < nRows; i++)
		{
			digitalWrite(keyboard[i][0].rowPin, HIGH); 
			for (uInt j = 0; j < nCols; j++)
			{
				sleep_for(milliseconds(25));
				if (keyboard[i][j].lastState)
				{
					if (! digitalRead(keyboard[i][j].colPin))
					{
						releaseKey(keyboard[i][j].keysym);
						keyboard[i][j].lastState = KEY_UP;
					}
					else continue; 
				}
				else 
				{
					if (digitalRead(keyboard[i][j].colPin))
					{
						pressKey(keyboard[i][j].keysym);
						keyboard[i][j].lastState = KEY_DOWN;
					}
					else continue;
				}

			}
			sleep_for(milliseconds(25));
			digitalWrite(keyboard[i][0].rowPin, LOW);
		}
		z++;
	}
}