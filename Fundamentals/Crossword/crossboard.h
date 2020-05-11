//Molly Doyle 
//Fundamentals of Computing 
//Lab 10 - crossword 
//header file - defining the crossboard class and all variables, etc. 

// including neccessary libraries 
#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream> 
#include <algorithm>

using namespace std;

const int SIZE =15;  // makes sure size of board stays constant and there are no accidental errors 
const char BLANK = '.'; // holding place for the board (got character frmo example on fund comp website 
const char EMPTY='#'; // empty space for the board  (got character from example on fund comp website 

class crossboard
{
	public: 
		crossboard(); 
		~crossboard(); 
		void getVec(); // cin usiner input 
		int getIfs(string);  // use ifs to get user input 
		int getOfs(string); // uses fstream output to displau solution 
		void displayBoard(); // displays the blank board, filled board, and clue 
		void addFirstWord();  // adds the longest entered word to the board first 
		void addOtherWords(); // adds remaining words by finding intersection 
		bool checkHorizontal(int, int, string); // seeing if there are any issues that would prevent a word from being added horizontally to the main crossboard 
		bool checkVertical(int, int, string); // seeing if there are any issues that would prevent a words from being added vertically to the main crossboard 
		void addHorizontal(int, int, string); // adding the words horizontally (must run checkHoriztonal first)
		void addVertical(int, int, string); // adding the words vertically (must run checkVertical first) 
		void clue(); // generates clue for a words by randoly shuffling the letters and displaying the direction of the word 
		// methods i had at one point but either added to other functions or split to be more specific to each case
		// bool checkValidity(string); 
		// void  makeCapital(vector<string>&)
		// void sortByLength(vector<string>)
		// void displayClue(); 
		// void displaySolution(); 
	
	private: 
		char mainboard[SIZE][SIZE];  // main board that creates array 
		vector<string> words; // words that the user wants to add to the crossword 
}
; 

