// Molly Doyle 
//Fundamentals of Computing - brickbreaker.cpp 

// including neccessary libraries 
#include <unistd.h>
#include "gfx.h"
#include <stdlib.h>

using namespace std; 
	
// including the header file
#include "brickbreaker.h"

// prototypes for bricks 
void paddle(int, int); 
void brick1(int); 
void brick2(int); 
void brick3(int); 
void brick4(int); 
void brick5(int); 
void brick6(int); 
void brick7(int); 
void brick8(int); 


brickbreaker::brickbreaker(){}

brickbreaker::~brickbreaker(){}

// creating paddle based on screen size and paddle size passed into it
void brickbreaker::paddle(int xc, int xP){
	gfx_color(246, 29, 224); 
	gfx_line(xc-30, 370, xc+30, 370); 
	gfx_line(xc-30, 395, xc+30, 395); 
	gfx_line(xc-30, 370, xc-30, 395); 
	gfx_line(xc+30, 370, xc+30, 395); 
}

	
void brickbreaker::brick1(int mrg){
	// top left brick 	
	gfx_line(mrg, mrg, mrg+100, mrg); 
	gfx_line(mrg, mrg+30, mrg+100, mrg+30); 
	gfx_line(mrg, mrg, mrg, mrg+30); 
	gfx_line(mrg+100, mrg, mrg+100, mrg+30); 
}

void brickbreaker::brick2(int mrg){
	// brick 2 in top line 
	gfx_line(2*mrg+100, mrg, 2*mrg+200, mrg); 
	gfx_line(2*mrg+100, mrg+30, 2*mrg+200, mrg+30); 
	gfx_line(2*mrg+100, mrg, 2*mrg+100, mrg+30); 
	gfx_line(2*mrg+200, mrg, 2*mrg+200, mrg+30); 
}

void brickbreaker::brick3(int mrg){
	// brick 3 in top line
	gfx_line(3*mrg+200, mrg, 3*mrg+300, mrg); 
	gfx_line(3*mrg+200, mrg+30, 3*mrg+300, mrg+30); 
	gfx_line(mrg*3+200, mrg, 3*mrg+200, mrg+30); 
	gfx_line(3*mrg+300, mrg, 3*mrg+300, mrg+30); 
}

void brickbreaker::brick4(int mrg){
	// brick 4 in top line 
	gfx_line(4*mrg+300, mrg, 4*mrg+400, mrg); 
	gfx_line(4*mrg+300, mrg+30, 4*mrg+400, mrg+30); 
	gfx_line(mrg*4+300, mrg, 4*mrg+300, mrg+30); 
	gfx_line(4*mrg+400, mrg, 4*mrg+400, mrg+30); 
}

void brickbreaker::brick5(int mrg){
	gfx_line(mrg, mrg+50, mrg+100, mrg+50); 
	gfx_line(mrg, mrg+80, mrg+100, mrg+80); 
	gfx_line(mrg, mrg+50, mrg, mrg+80); 
	gfx_line(mrg+100, mrg+50, mrg+100, mrg+80); 
}

void brickbreaker::brick6(int mrg){
	// brick 2 in second line
	gfx_line(2*mrg+100, mrg+50, 2*mrg+200, mrg+50); 
	gfx_line(2*mrg+100, mrg+80, 2*mrg+200, mrg+80); 
	gfx_line(2*mrg+100, mrg+50, 2*mrg+100, mrg+80); 
	gfx_line(2*mrg+200, mrg+50, 2*mrg+200, mrg+80); 
}

void brickbreaker::brick7(int mrg){
	// brick 3 in second line 
	gfx_line(3*mrg+200, mrg+50, 3*mrg+300, mrg+50); 
	gfx_line(3*mrg+200, mrg+80, 3*mrg+300, mrg+80); 
	gfx_line(mrg*3+200, mrg+50, 3*mrg+200, mrg+80); 
	gfx_line(3*mrg+300, mrg+50, 3*mrg+300, mrg+80); 
}

void brickbreaker::brick8(int mrg){
	// brick 4 in second line 
	gfx_line(4*mrg+300, mrg+50, 4*mrg+400, mrg+50); 
	gfx_line(4*mrg+300, mrg+80, 4*mrg+400, mrg+80); 
	gfx_line(mrg*4+300, mrg+50, 4*mrg+300, mrg+80); 
	gfx_line(4*mrg+400, mrg+50, 4*mrg+400, mrg+80); 
}



