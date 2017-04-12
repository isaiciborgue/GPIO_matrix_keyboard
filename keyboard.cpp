/* 	
 *	g++ -Wall -std=c++11 -o joypad keyboard.cpp MatrixKeyboard.cpp -lwiringPi -lX11 -lXext -lXtst 
 */

#include "MatrixKeyboard.hh"

int main()
{
	vector<uInt> rows;
	vector<uInt> cols;
	vector<KeySym> keys;

	// rows
	rows.push_back(23);
	rows.push_back(24);
	rows.push_back(25);


	// columns
	cols.push_back(27);
	cols.push_back(28);
	cols.push_back(29);

	// Keys
	keys.push_back(XK_Up);
	keys.push_back(XK_Left);
	keys.push_back(XK_Down);
	
	keys.push_back(XK_Right);
	keys.push_back(XK_s);
	keys.push_back(XK_a);
	
	keys.push_back(XK_z);
	keys.push_back(XK_x);
	keys.push_back(XK_Return);

	MatrixKeyboard myKeyboard(rows, cols, keys);

	myKeyboard.run();
	
	return 0;
}
