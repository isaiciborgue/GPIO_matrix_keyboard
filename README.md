# GPIO_matrix_keyboard
A GPIO matrix keyboard for Raspberry Pi, using X11.

# How to compile via terminal
`g++ -Wall -std=c++11 -o joypad keyboard.cpp MatrixKeyboard.cpp -lwiringPi -lX11 -lXext -lXtst`
