// Molly Doyle 
// Fundamentals of Computing - Lab 10 Crosword 
// crossboard.cpp - class implementation file 

// including neccessary libararies 
#include <iostream> 
#include <vector> 
#include <string> 
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std; 

#include "crossboard.h" // including header file 

crossboard::crossboard() //creating blank outline for the board 
{
	for (int i=0; i<SIZE; i++){
		for (int j=0; j<SIZE; j++){
			mainboard[i][j] = BLANK; 
		}
	}
}

crossboard::~crossboard(){} // deconstructor 

int crossboard::getIfs(string file) // reads in words using ifstream 
{
	ifstream ifs; // creating ifs using ifstream
	
	ifs.open(file); // reading in file 

	if(!ifs){
		cout << "Error: Could not open file " << file << endl; 
		return 1; 
	}

	string word; // declaring string variable that will be given value from ifs stream  
	
	// reading in text until end of file while not suprassing actual contents 
	while(ifs.peek()!=EOF){
		getline(ifs, word); 
		words.push_back(word); 
	}
	
	// converting all text to upper cases for consistent comparison by altering actual value in memory 
	for (auto it=words.begin(); it!=words.end(); it++){
		for (auto jt=(*it).begin(); jt!=(*it).end(); jt++){
			*jt = toupper(*jt);
		}
	}
	// storing words according to their lengths so that the olargest are lsited first 
	for(int i=0; i <words.size()-1; i++){
		for (int j=0; j<words.size()-i; j++){
			if(j!=words.size()-1-i){
				int a = words[j].length(); 
				int b = words[j+1].length(); 
				if(b>a){ // comparing word length to get the longest word in first position and the rest following 
					string store = words[j]; 
					words[j]=words[j+1]; 
					words[j+1]=store; 
				}
			}
		}
	}
	return 0; 
}

void crossboard::getVec() // takes in words by prompting user and using cin 
{
	string text; // stores user input 
	int count=0; // keeps track of number of words inputted by the user
	
	cout << "Enter max of 20 words to put into a crossword, followed by '.': "; // prompting for user input
	
	getline(cin, text); // reading in userinput
	
	while(text!="." && count <20){
		if(text.size()>15 || text.size()<2){ // checking validity of user input 
			cout << "Please enter a new set of words (2 minimum, 20 maximum): " << endl; 
			getline(cin, text); 
		}
		else { // while input is valid :)
			for (auto it=text.begin(); it!=text.end(); it++){
				(*it)=toupper(*it); // convreting input to upper for consistent comparison 
			}
			words.push_back(text); 
			getline(cin, text); 
			count++; 
		}
	}

	for (int i=0; i<words.size()-1; i++) { // for loop to store all words (-1 to account for index starting at 0) 
		for (int j=0; j<words.size()-i; j++){
			if(j!=words.size()-1-i){
				int a = words[j].length(); 
				int b = words[j+1].length(); 
				if(b>a){ // compares lengths of the inputted words so that it
					string store = words[j]; 
					words[j]=words[j+1]; 
					words[j+1]=store; 
				}
			}
		}
	}
}

int crossboard::getOfs(string file){ // reading in words for crossword using argv 
	ofstream ofs; 
	
	ofs.open(file); 
	if(!ofs){
		cout << "Error: invalid file " << endl; 
		return 2; 
	}
	
	ofs << endl << "Crossword Solution: " << endl; 
	
	addFirstWord(); // callign method to add furst word to the crossword (first word being the longest word) 
	addOtherWords(); // adds remaining words that are shorter than the first word 
	

	// formatting for blank board using - and |
	ofs << "-"; // - for corner formatting 
	
	for(int i=0; i<SIZE; i++){ // creates horizontal line for board 
		ofs << "-"; 
	}

	ofs << "-" << endl; 
	 
	for(int i=0; i<SIZE; i++){
		ofs << "|"; 
		for(int j=0; j<SIZE; j++){
			ofs << mainboard[i][j]; 
		}
		ofs << "|"  << endl; 
	}

	ofs << "-" << endl << endl; 

	// dispaying the crossword using # and ' ' (blank crossword) 
	ofs << "Crossword Puzzle: " << endl; 

	ofs << "-"; 
	for (int i=0; i<SIZE; i++){
		ofs << "-";
	}
	ofs << "-" << endl; 

	for (int i=0; i<SIZE; i++){
		ofs << "|"; 
		for(int j=0; j<SIZE; j++){
			if (mainboard[i][j] != '.'){
				ofs << ' '; 
			}
			else {
				ofs << '#';
			}
		}
	ofs << "|" << endl; 
	}
	
	ofs << "-"; 
	for(int i=0; i<SIZE; i++){
		ofs << "-"; 
	}

	ofs << "-" << endl; 

	// clues for the words by shuffling the letters 
	// tried to have this as its own method in the class but could not get it to work. Moved it back but not sure if moving this caused a problem 
	ofs << "Clues: " << endl << endl; 
	for (int i=0; i<words.size(); i++){ // iterates through each element 
		for (int x=0; x<SIZE; x++){
			for (int y=0; y<SIZE; y++){
				if (mainboard[x][y] == words[i][0] && mainboard[x+1][y]==words[i][1] && mainboard[x+2][y] == words[i][2]){
					random_shuffle(words[i].begin(), words[i].end()); 
					ofs << x << ", " << y << " Down " << words[i] << endl;  // shuffling letters 
				}
				else if (mainboard[x][y] ==words[i][0] && mainboard[x][y+1]==words[i][1] && mainboard[x][y+2] == words[i][2]){
					random_shuffle(words[i].begin(), words[i].end()); 
				}
			}
		}
	}
}
				
	



void crossboard::displayBoard(){ // displaying he crossboard, solution, and crossword puzzle 
	cout << endl << endl << endl; 
	
	cout << "Solution to your crossword: " << endl; 
	
	addFirstWord(); 
	addOtherWords(); 	
	
	cout << "-"; 

	for(int i=0; i<SIZE; i++){ // creating horiztonal edge of board
		cout << "-"; 
	}
	
	cout << "-" << endl; // corner 
	for(int i=0; i<SIZE; i++){
		cout << "|"; 
		for(int j=0; j<SIZE; j++){
			cout << mainboard[i][j]; 
		}
		cout << "|" << endl; 
	}
	
	cout << "-"; //corner piece
	
	for(int i=0; i<SIZE; i++){
		cout << "-"; 
	}
	
	cout << "-" << endl << endl; // corner piece

	// shows board with outlines of missing words 
	cout << "Crossword Puzzle: " << endl; 
	
	cout << "-" ;

	for(int i=0; i<SIZE; i++){
		cout << "-"; 
	}
	
	// creating the board using - and | 
	cout << "-" << endl; 

	for (int i=0; i<SIZE; i++){
		cout << "|"; 
		for(int j=0; j<SIZE; j++){
			if(mainboard[i][j]!= '.'){
				cout << ' '; 
			}
			else {
				cout << '#'; 
			}	
		}
		cout << "|"; 
		cout << endl; 
	}	

	cout << "-"; 
	for (int i=0; i<SIZE; i++){	
		cout << "-"; 
	}
	cout << "-" << endl; 
}
	

void crossboard::addFirstWord() // adding longest word to the middle of the board 
{
	// 
	int sz=(words[0].length()); 
	int loc=(sz-3)/2; 
	int mid=6-loc;  //getting middle of the board based on the board length 
	int row = 7; 
	
	for (int i=0; i<sz; i++){
		mainboard[row][i+mid]=words[0][i];  // putting longest board in the middle row 
	}
}
// adding remainder words after longest word has been added 
void crossboard::addOtherWords(){
	for (int i=1; i!=words.size(); i++){ // size of the added words 
		for (int j=0; j<words[i].size(); j++){ // size of added words
			for (int x=0; x<SIZE; x++){ // iterating through added words 
				for (int y=0; y<SIZE; y++){ // iterating through added words 
					if(words[i][j]==mainboard[x][y]){
						if(checkVertical(x,y,words[i])==true){ // using verticla method to see if it can be placed ertically first 
							x=SIZE; // giving x and y values 
							y=SIZE; 
							j=words[i].size(); 	
						}
						else if(checkHorizontal(x,y,words[i])==true){ // checkign to see if it can be horizontal 
							x=SIZE; 
							y=SIZE; 
							j=words[i].size(); 
						}
					}
				}
			}
		}
	}
}

// adding vertical word checking beginnign and ending coordinates 
void crossboard::addVertical(int x, int y, string text)
{
	int L=text.length(); 
	int count = 0;
	int s = 0;
	
	while(mainboard[x][y]!=text[s]){ // getting count and s values 
		count++; 
		s++; 
	}
	
	int loc=0; 
	
	// getting the middle of the board based on the word length 
	int beg = x-count; 
	int end = beg+L; 

	// adding word based on found middle ^^ 
	for (int i=beg; i<end; i++){
		mainboard[i][y]=text[loc]; 
		loc++;
	}
}

// checking if vertical will fit 
bool crossboard::checkVertical(int m, int n, string text)
{
	int count = 0;
	int s=0; 
	
	while(mainboard[m][n]!=text[s]){
		count++; 
		s++; 
	}
	
	count++; 
	
	int beg=n-count; 
	int L=text.length();
	int c =0; 
	
	for(int x=beg; x<=beg+L+1; x++){ // checkign surrounding spaces for interference 
		for(int y=n-1; y<=n+1; y++){
			if(x!=m){
				if(x<16 && x>=0 && y>=0 && y<16){
					if(mainboard[x][y]!='.'){
						c++; 
					}
			}
		}
	}

	if (c==0){ // checks to see if any errors or problems with added the word vertically to the board  
		addVertical(m,n, text); 
		return true; 
	}
	else {
		return false; 
	}
}
}

void crossboard::addHorizontal(int x, int y, string text){ // adding a horizontal word to the board 
	int L = text.length(); 
	int count =0; 
	int c = 0; 
	
	while(mainboard[x][y]!=text[c]){ // counting by adding to count and c 
		count++; 
		c++; 
	}
	
	// finding the middle of the board based on word length 
	int loc = 0;  
	int beg = y-count;  
	int end = beg + L ; 
	
	for(int i = beg; i<end; i++){ // iterating through mainboard and text 
		mainboard[x][i]=text[loc]; 
		loc++; 
	}
}

bool crossboard::checkHorizontal(int m, int n, string text) // checking to see if the horizontal 
{
	int count = 0; 
	int c=0; 
	
	while(mainboard[m][n]!=text[c]){ // count a dn c 
		count++; 
		c++; 
	}
	
	count++; 

	 // finding middle of the board 
	int beg = n-count; 
	int L = text.length();
	int check = 0; 
	
	// iterating through possible y values 
	for (int y=beg; y <=beg+L+1; y++){
		for(int x = m-1; x<=m+1; x++){
			if(y!=n){
				if(x<16 && x>=0 && y>=0 && y<16){
					if(mainboard[x][y]!='.'){
						check++;  // checking if there are any occupied spaces near where the words is tryign to be entered 
					}
				}	
				else if(y>15 || y<-1){
					check++; 
				}
			}
		}
	}
	
	if(check==0){ // if check >1, there was an error (see for loop above) so the owrd cannot be added in that location 
		addHorizontal(m,n,text); 
		return true; 
	}
	else {
		return false;
	}
}

void crossboard::clue() { 
// used to have this as a struct but when i tried to change it and some of my other functios into methods i got alot of errors then it compiled but i got a segmentation failure. Dont know where i went wrong but didnt have time to fix it 
	cout << endl << "Clues for your crossowrd: " << endl << endl; 
	for (int i=0; i<words.size(); i++){
		for (int x=0; x<SIZE; x++){
			for (int y=0; y<SIZE; y++){
				if(mainboard[x][y]==words[i][0] && mainboard[x+1][y]==words[i][1] && mainboard[x+2][y]==words[i][2]){
					random_shuffle(words[i].begin(), words[i].end()); // using random_shuffle function to swithc order of letters in the word around 
					cout << x << ", " << y << " Down " << left << words[i] << endl;  // 
				}
				else if (mainboard[x][y]==words[i][0] && mainboard[x][y+1]==words[i][1]&& mainboard[x][y+2]==words[i][2]){
					random_shuffle(words[i].begin(), words[i].end()); 
					cout << x << ", " << y << " Across " << words[i] << endl; // gives location and and direction 
				}
			}
		}
	}
}
			

