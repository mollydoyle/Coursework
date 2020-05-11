// Molly Doyle 
// Fundamentals of computing - project.cpp 
// main file for final project. implements classes that create a brick breaker type game

// including neccessary libraries including the header file and the gfx.h library 
#include <unistd.h>
#include "gfx.h"
#include <stdlib.h>
#include "brickbreaker.h"
using namespace std;


// creating function prototypes 
void instructions(int, int); 
void loser(int, int); 
void winner(int, int); 
	
int main(){

	brickbreaker brick;// creating an instance of the brickbreaker class  

	char c = 0; // will read user input 
	int width = 500, height = 400; // bounds for display 
	float xc = 300, yc = 200; // initial ball coordinates
	int rad = 10; // ball radius
	float vx = 6, vy =2; // ball speed
	int mrg = 20; // margin of bricks in relation ot edge of the board 
	int bxsz = 100; // brick length 
	int bysz = 30; // brick height
	bool b1 = true, b2 = true, b3 = true, b4 = true, b5 = true, b6 = true, b7=true, b8=true;  // boolean as status for each brick
	int brickCount = 8; // keeps count of remaining bricks 
	int pL = 60; // paddle size 
	int xp = width/2; 

	gfx_open(width, height, "Brick Breaker"); // opening a graphics window titled "Brick Breaker" 
	
	
	while(c != 'q'){
		gfx_clear(); 
	
		gfx_color(239, 255, 0); 
		gfx_circle(xc, yc, rad);  // creating ball
		

		if(gfx_event_waiting()){
			c = gfx_wait(); // waiting to read in user input 
		}

		if(c == 'S'){ // user presses right arrow 
			xp =xp+15; // paddle moves to right 
			c = 'a'; // changing c to arbitrary value 
		}
		if(c == 'Q'){ // user presses left arrow 
			xp = xp-15; // paddle moves to left 
			c = 'a'; // changing c to arbitrary value 
		}
		
		brick.paddle(xp, pL); // creating paddle from class 
		
		gfx_color(29, 246, 239); 

		// ADDING STILL AVAIABLE BRICKS TO THE DISPLAY 
		if (b1==true){
			brick.brick1(mrg); // if brick 1 status is true, it will be added to the screen 
		}
		if (b2==true){
			brick.brick2(mrg);// if brick 2 status is true, it will be added to the screen 
		}
		if(b3==true){
			brick.brick3(mrg);// if brick 3 status is true, it will be added to the screen 
		}
		if(b4==true){
			brick.brick4(mrg); // if brick 4 status is true, it will be added to the screen 
		}
		if(b5==true){
			brick.brick5(mrg); // if brick 5 status is true, it will be added to the screen 
		}
		if(b6==true){
			brick.brick6(mrg); // if brick 6 status is true, it will be added to the screen 
		}
		if(b7==true){
			brick.brick7(mrg); // if brick 7 status is true, it will be added to the screen 
		}
		if(b8==true){
			brick.brick8(mrg);// if brick 8 status is true, it will be added to the screen 
		}
		

		gfx_color(255, 255, 255); // giving ball white color 
		xc += vx; // moving ball at natural slow speed in x direction
		yc += vy; // moving ball at natural slow speed in y direction 

		// BALL WALL INTERACTIONS 
		if(xc >= width - rad){ // right wall 
			vx = -vx; // changes ball direction when it hits side wall
			xc = width - rad; 
		}
		if(xc <= 10){ // left wall 
			vx = -vx;  // changes ball direction when it hits the left wall
		}
		if(yc <= 10){ // top wall
			vy = -vy; // reflect ball down if it hits the top wall 
		}
		
		// BALL PADDLE INTERACTIONS  
		if (yc+rad==370 && xc<(xp+pL/2) && xc>(xp-pL/2)){ // if ball reaches height of paddle and its center hits the paddle, it bounces in opposite direction 
			vy =-vy; 
		}

		// BALL-BRICK INTERACTIONS  
		if (b1 == true && (yc+rad<=70 && yc+rad >= 20) && (xc>mrg && xc<(mrg+bxsz))){ // if ball hits the top left brick brick dimensions
			brickCount = brickCount-1; // total brick count -1 
			b1 = false; // boolean value false so wont appear on screen again 
			vy=-vy; // reflected in opposite y direcition 
		}
		if (b2 == true && (yc+rad<=70 && yc+rad >=20) && (xc>(2*mrg+bxsz) && xc<(mrg*2+bxsz*2))){ // if ball hits second brick from left in top row 
			brickCount = brickCount-1; // total brick count - 1
			b2=false;  // boolean value false so wont appear on screen again 
			vy=-vy; // reflected in opposite y direction 
		}
		if (b3 == true && ((yc+rad)<=70 && (yc+rad) >=20) && (xc>(3*mrg+bxsz*2) && xc<(mrg*3+bxsz*3))){ // if ball hits second brick from right in top row 
			brickCount = brickCount-1; // total brick count - 1
			b3= false;  // boolean value false so wont appear again 
			vy=-vy; // reflected in opposite y direction 
		}
		if (b4 == true && (yc+rad<=70 && yc+rad>=20) && (xc>(4*mrg+bxsz*3) && xc<(mrg*4+bxsz*4))){ // if ball hits the right top brick it
			brickCount = brickCount-1; // total brick count -1 
			b4= false; // boolean value false so wont appear again 
			vy=-vy; // reflected in opposite y direction 
		}
		if(b5 == true && (yc+rad<=(mrg*2+30)+50 && yc+rad >= (mrg*2+30*2)) && (xc>mrg && xc<(mrg+bxsz))){ // if ball hits the lower left brick 
			brickCount = brickCount-1; // total brick count - 1 
			b5 = false; // boolean value false so wont appear again 
			vy=-vy; // reflected in opposite y direction 
		}
		if (b6 == true && (yc+rad<=(mrg*2+30)+50 && yc+rad >=(mrg*2+30*2)) && (xc>(2*mrg+bxsz) && xc<(mrg*2+bxsz*2))){ // if ball hits the lower second from left brick 
			brickCount = brickCount-1; // total brick count - 1 
			b6=false; // boolean value false so wont appear again 
			vy=-vy;  // reflected in opposite y direction 
		}
		if (b7 ==true &&(yc+rad<=(mrg*2+30)+50 && yc+rad>=(mrg*2+30*2)) && (xc>(3*mrg+bxsz*2) && xc<(mrg*3+bxsz*3))){ // if ball hits lowed second from right brick 
			brickCount = brickCount-1; // total brick count - 1 
			b7= false; // boolean value false so wont appear again 
			vy=-vy;  // reflected in opposite y direction 
		}
		if (b8 == true && (yc+rad<=(mrg*2+30)+50 && yc+rad>=((mrg*2+30*2))) && (xc>(4*mrg+bxsz*3) && xc<(mrg*4+bxsz*4))){ // if ball hits lower right brick 
			brickCount = brickCount-1; // total brick count - 1 
			b8= false;  // boolean value false so wont appear again 
			vy=-vy; // reflected in opposite y direction 
		}

		// END CONDITIONS
		gfx_color(255, 255, 255); 
		if (brickCount>0&& (yc+rad<height)){
			instructions(width, height);
		}
		else if(brickCount ==0){ // brick count 0 so  no more remaining 
			winner(width, height); 
		}
		else if ((yc+rad)>=height){ // ball goes lower than paddle height, so game ends 
			loser(width, height); 
		}

		//WAITING TO READ IN USER INPUT 
		if(gfx_event_waiting()){
			c = gfx_wait(); // waiting to read in user input 
		}

		
		gfx_flush(); 
		usleep(100000); 
	}


	
	return 0; 
}

// displays instructions as text to the user 
void instructions(int width, int height){
	gfx_text(width/2 - 70, height/2, "Welcome to Brickbreaker!"); 
	gfx_text(width/2 - 200, height/2 + 25, "Destroy all the bricks by moving the paddle with the arrow keys."); 
}
// displays ending text signifying loss to the user 
void loser(int width, int height){
	gfx_text(width/4+20, height/2, "Game Over! You let the ball drop."); 
	gfx_text(width/4+30, height/2+15, "Enter 'q' to close the screen."); 
}

// displays ending text signifying win to the user 	
void winner(int width, int height){
	gfx_text(width/4+20, height/2, "Congrats! You destroyed all the bricks!"); 
	gfx_text(width/4+30, height/2+15, "Enter 'q' to close the screen."); 
}
		
