//Molly Doyle
//Fund Comp - Lab 9 
//Game of life - life.cpp

// including all neccessary libraries including the header file so that all functions are defined and accessed 
#include <iostream> 
using namespace std; 
#include <stdlib.h>
#include<unistd.h>
#include<fstream>
#include "lifeboard.h"

// defining prototype for menu 
void menu(char &); 

// main function using argc, and *argv 
int main(int argc, char *argv[])
{
	// creating an instance of Lifeboard and values of x and y that will be used throughout the program 
	Lifeboard Life; 
	int x, y; 

	char choice='i'; 

	// if statement based on command line parameters 
	if (argc==1){
		Life.displayBoard();
		// using switch case to get users desired action 
		while(choice!='q'){
			menu(choice);
	
			switch(choice){
				case 'a': // adding a cell 
					cout << "Enter x: " ; 
					cin >> x; 
					cout << "Enter y: "; 
					cin >> y; 
					Life.addCell(x,y); // adding cell in users desired location and displaying the board with the cell added using functions from the header file  
					Life.displayBoard(); 
					break; 
				case 'r': // removing a cell 
					cout << "Enter x: "; 
					cin >> x; 
					cout << "Enter y: "; 
					cin >> y; 
					Life.removeCell(x,y); // using removeCell function from header  
					Life.displayBoard(); 
					break; 
				case 'n': 
					Life.advance(); // using the advance function to simulate how cells movement would progress based on current board status 
					break; 
				case 'q': 
					break; // ending the program 
				case 'p': // playing the game continuously until it is over and clearing the board 
					while(true){
						Life.advance(); 
						Life.displayBoard(); 
						usleep(200000); 
						system("clear"); 
				} 		
				break; 
			}
		}
}
	else if(argc==2){
		// makign sure file is able to be opened and giving an error if it is not 
		ifstream ifs; 
	
		ifs.open(argv[1]); 
		if(!ifs){
			cout << "Error opening file " << argv[1] << endl; 
			return 1;
		}
		char choice2; 
	
		while(choice2!='q'){
			 
			
			ifs >> choice2 ; 
			
			// using another switch to define choice after notifying the user of an error in the file using user input 
			switch(choice2){
				// reads in x and y values from file rather than prompting the user
				case 'a': 
					ifs >> x; 
					ifs >> y; 
					Life.addCell(x,y); // adds cell to the board and displays it using function 
					Life.displayBoard(); 
					break; 
				case 'r': 
					ifs >> x; 
					ifs >> y;
					Life.removeCell(x,y); // removes desired cell from the board using function 
					Life.displayBoard(); 
					break; 
				case 'n': 
					Life.advance(); // advances life using function 
					break; 
				case 'q':
					break; // quits the program 
				case 'p': 
					while(true){
						Life.advance(); 
						Life.displayBoard(); 
						usleep(200000); 
						system("clear"); 
					}
			}
		}
	}
	else {
		cout << "Error with input" << endl; 
	}

	return 0; 
} 

// menu function that displays all of the options possible 
void menu(char & character)
{
	cout << "Enter a choice: " << endl; 
	cout << "a: Enter coordinates to add a new live cell" << endl; 
	cout << "r: Enter coordinates to remove a live cell" << endl; 
	cout << "n: Advance the simulation" << endl; 
	cout << "q: Quit the program" << endl; 
	cout << "p: Play the game continuously" << endl; 
	cin >> character; 
}


		
