// MOlly Doyle 
// Fundamentals of computing - brick breaker header file 
#include <iostream>
#include "gfx.h"
#include <stdlib.h>

class brickbreaker // defining class 
{
	public: 
		brickbreaker(); // instance of class 
		~brickbreaker(); // destructor 
		void paddle(int, int); // creates paddle on display 
		void brick1(int); // creates brick 1 on display 
		void brick2(int); // creates brick 2 on display 
		void brick3(int); // creates brick 3 on display 
		void brick4(int); // creates brick 4 on display 
		void brick5(int); // creates brick 5 on display 
		void brick6(int); // creates brick 6 on display 
		void brick7(int); // creates brick 7 on display 
		void brick8(int); // creates brick 8 on display 
		char displayMenu(int, int);  // displays the menu of options at the beginning of the program 
};
