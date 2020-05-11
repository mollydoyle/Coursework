//Molly Doyle
//Fundamentals of Computing 
//Lab 9 - Game of Life Header file lifeboard.h
#include <iostream> 

using namespace std; 

// intializing global variables used throughout the program 
const int SIZE = 40; 
const char ALIVE = 'X'; 
const char DEAD = ' '; 
const char BLANK = ' '; 

// defining functions for the Lifeboard class 
class Lifeboard
{
	public: 
		Lifeboard(); 
		~Lifeboard(); 
		void displayBoard(); 
		void addCell(int, int); 
		void removeCell(int, int); 
		void advance(); 
		void checkBoard(int, int); 
	private: // initializes temporary and main boards used to simulate the 'game of life' 
		char tmpboard[SIZE][SIZE];
		char mainboard[SIZE][SIZE];
};
