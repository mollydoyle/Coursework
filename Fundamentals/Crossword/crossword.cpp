//Molly Doyle 
//Fundmanetals of computing - crossword lab 10 
//main function 

// including neccessary libaries 
#include <iostream> 
#include <vector> 
#include <string> 
#include <algorithm> 
#include <iomanip> 
#include <fstream> 

using namespace std; 


#include "crossboard.h" // including crossboard.h header file 

int main(int argc, char *argv[])
{
	crossboard c1; // creating an instance of the class to be used throughout the program

	vector<string> wordList;
	// was advised by ta to make as efficent as possible by using functions for Vec and IFS. Worked when wasnt in functions but couldnt get it to work as functions. Stuck in an infinite loop. Didnt have time to fix it. 
	// Had sort struct for clues but was told it might be easier to make it a function. Somewhere along the way when i chenged my program  it stopped working and i get a segmentation fault 
	
	if (argc==1){
		c1.getVec(); 	// uses getline to read in input 
		c1.displayBoard(); 
		c1.clue(); 
	} 
	else if(argc==2){ // ifs stream to read in input 
		c1.getIfs(argv[1]); 
		c1.displayBoard(); // display finction 
		c1.clue(); 
	} 
	else if(argc==3){ // streaming from command line 
		c1.getIfs(argv[1]);
		c1.getOfs(argv[2]); 
	}
	else {
		cout << "Too many arguments" << endl; 
	}
return 0; 
}

