// Molly Doyle 
// Fundamentals of Computing - Lab 9 
// Game of Life - lifeboard.cpp


#include <iostream> 
#include <string> 
using namespace std; 
// including the header file so that all functions are can be defined 
#include "lifeboard.h"

Lifeboard::Lifeboard() 
{
	// creating lifeboard according the size (global variable) set in the header file 
	for (int i=0; i<SIZE; i++){
		for (int j=0; j<SIZE; j++){
			mainboard[i][j]=BLANK; 
			tmpboard[i][j]=BLANK; 
		} 
	} 
} 

// defining the deconstructor 
Lifeboard::~Lifeboard(){ } 

void Lifeboard::displayBoard()
{ 
	// creating grid using -, |, and + 
	cout << "+"; 
	for (int i=0; i<SIZE; i++){
		cout << "-"; 
	} 
	cout << "+"; 
	cout << endl; 
	for (int i=0; i<SIZE; i++){
		cout << "|"; 
		for (int j=0; j<SIZE; j++){
			cout << mainboard[i][j]; 
		}
		cout << "|" << endl; 
	} 
	
	cout << "+"; 
	for (int i=0; i<SIZE; i++){
		cout << "-"; 
	}
	cout << "+"; 
	cout << endl; 
}

void Lifeboard::addCell(int x, int y)
{
	// giving ALIVE value to cell in mainboard 
	mainboard[y][x]=ALIVE; 
} 

void Lifeboard::removeCell(int x, int y)
{
	// giving DEAD value to cell in mainboard 
	mainboard[y][x]=DEAD; 
}

void Lifeboard::advance()
{
	// confirming conditions that allow the cell to advance by locating the desired cell and using the checkboard function 
	for (int i=0; i<SIZE; i++){
		for (int j=0; j<SIZE; j++){
			this ->checkBoard(i,j); 
			
		}
	}
	// making setting the mainboard equal to the temporary board and displaying it 
	for (int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			mainboard[i][j]=tmpboard[i][j]; 
		} 
	} 
	this->displayBoard(); 
} 

void Lifeboard::checkBoard(int x, int y)
{
	// checking to see the status of the cell in the board using count, then modifying count to reflect if the cell is dead or alive; uses rules from article that decide status of the cell 
	int status=0; 
	for (int i=-1; i<=1; i++){
		for(int j=-1; j<=1; j++){
			if(x+i>=0 && x+i<SIZE && y+j>=0 && y+j<SIZE){
				if (mainboard[x+i][y+j]==ALIVE){
					status++; 
				} 
			}
		}
	}


	// uses rules from the article to see if cell should be declared dead or alive and declares it 
	if (mainboard[x][y]==ALIVE){
		status =status-1; 
	}

	if(mainboard[x][y]==ALIVE && (status==2 || status==3)){
		tmpboard[x][y]=ALIVE; 
	}
	else if(mainboard[x][y]==ALIVE){
		tmpboard[x][y]=DEAD;
	}
	else if(mainboard[x][y]==DEAD && status==3){
		tmpboard[x][y]=ALIVE; 
	}
	else{
		tmpboard[x][y]=DEAD; 
	}
}
