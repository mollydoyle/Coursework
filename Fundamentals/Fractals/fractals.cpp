// Molly Doyle 
// Fundamentals of Computing - Fractals 
// implements given code by usign a switch case to display various recursive images 

// Including neccessary libraries 
#include <iostream> 
#include "gfx.h"
#include <cmath> 

using namespace std; 

// function prototypes 
void displayMenu(); //menu prototype
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 ); // prototype for sierpinkski triangle fractal
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 ); // prototype to draw a basic triangle 
void drawSquare( double xc, double yc, double length ); // prototype to draw a basic square
void drawSpiral (double x, double y, double radius1, double radius2, double theta ); // prototype to draw a basic spiral
void shrinkingSquares( double xc, double yc, double length ); // prototype for shrinking square fractal 
void spiralSquares( double xc, double yc, double length, double theta );  // prototype for spiral square fractal 
void circularLace( double xc, double yc, double radius ); // prototype for circular lace fractal
void snowflake( double x, double y, double radius, double theta );  // prototype for snowflake fractal 
void tree( double x, double y, double length, double theta ); // prototype for tree fractal 
void fern( double x, double y, double length, double theta ); // prototype for fern fractal 
void spiralOfSpirals( double x, double y, double length, double radius, double theta ); // prototype for spiral of spirals fractal 



int main() {
	int width = 700, height = 700, mrgn = 20; // dimensions for size of board nad boundaries 
	bool loop = true; // determines how long the lop runs 
	char c; // char var to store user input 

  	gfx_open(width, height, "Fractals" ); // opens display titled "Fractals"
	gfx_clear(); 
	displayMenu(); // displays the menu of options 
	
  	while (loop) {
    	c = gfx_wait(); // waits to read in user input 
    	gfx_clear();
    	switch (c) {
      		case '1': // Sierpinski Triangle   
				gfx_clear();
        		sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);  //calls the sierpinksi function centered in the board 
        		break;
			case '2': 
				gfx_clear(); 
				shrinkingSquares(width/2, height/2, height/2); // calls the shirkingSquares function centered in the baord 
				break; 
			case '3': 
				gfx_clear(); 
				spiralSquares(width/2, height/2, 1, 0); // calls the spiralSquares function centered in the board 
				break; 
			case '4': 
				gfx_clear(); 
				circularLace(width/2, height/2, width/2 - mrgn*6); // calls the circularLace function in the middle of the board 
				break; 
			case '5': 
				gfx_clear(); 
				snowflake(width/2, height/2, width/2-mrgn*7, 3*M_PI/10);// calls the snowflake function in the middle of the board 
				break; 
			case '6':
				gfx_clear(); 
				tree(width/2, height, width/2-mrgn*8,0); // calls the tree function in the middle of the board 
				break;
			case '7':
				gfx_clear();
				fern(width/2, height-mrgn, height/2-mrgn*4, 0); // calls the fern function in the middle of the board 
				break; 
			case '8':
				gfx_clear(); 
				spiralOfSpirals(width/2, height/2, 1, 1, 2*M_PI/3); // calls the spiralOfSPrials in the middle of the board 
				break; 
			case 'q':
				loop = false; // ends the program by changing the value of the loop bool variable 
				break; 
			case 'm': 
				gfx_clear(); 
				displayMenu(); // calls the displayMenu function again if desired by the user 
				break; 
				
    }
  }

  return 0;
}


// function to create sierpinksi triangle (given on course website)
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
	if( abs(x2-x1) < 5 ) // checks validity of the bounds 
		return;
	
	drawTriangle( x1, y1, x2, y2, x3, y3 ); // uses drawTriangle function to draw a basic triangle as the basis of the triangle
	
	// 3 recursive calls to complete the sierpinski triangle as show on the course website 
	sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 ); 
 	sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  	sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
 }

// function to draw the triangle (used in sierpinksi function 
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  	gfx_line(x1,y1,x2,y2); //line connecting point 1 to point 2 
  	gfx_line(x2,y2,x3,y3); // line connecting point 2 to point 3 
  	gfx_line(x3,y3,x1,y1); // line connecting point 3 to point 1 
}
  
void displayMenu() // function that displays a menu of options for user input 
{
	gfx_color(255, 255, 255); 
	gfx_text(205, 150, "Enter 1 to display a sierpinski triangle fractal");
  	gfx_text(205, 165, "Enter 2 to display a shrinking square fractal");
  	gfx_text(205, 180, "Enter 3 to display a spiral square fractal");
  	gfx_text(205, 195, "Enter 4 to display a circular lace fractal");
  	gfx_text(205, 210, "Enter 5 to display a snowflake fractal");
  	gfx_text(205, 225, "Enter 6 to display a tree fractal");
  	gfx_text(205, 240, "Enter 7 to display a fern fractal");
  	gfx_text(205, 255, "Enter 8 to display a sprial of spirals fractal");
	gfx_text(205, 270, "Enter 'm' to display the menu again.");
	gfx_text(205, 285, "Enter 'q' to quit the program"); 
}

void drawSquare(double xc, double yc, double length) // draws basic square shape 
{
	gfx_line( xc-length/2, yc-length/2, xc+length/2, yc-length/2 ); // lower horizontal line of square 
	gfx_line( xc+length/2, yc-length/2, xc+length/2, yc+length/2 );	// right vertical line of square 
	gfx_line( xc+length/2, yc+length/2, xc-length/2, yc+length/2 ); // higher horizontal line of square 
	gfx_line( xc-length/2, yc+length/2, xc-length/2, yc-length/2 ); // left vertical line of square 
}  

void drawSpiral(double x, double y, double radius1, double radius2, double theta ) //draws basic spiral shape 
{
	if ( radius2 >= radius1/3 ) { 
		return; 
		}

	gfx_point( x, y );

  	radius2 = 1.1*radius2; // increases raidus size by small increment 
  	theta = theta-(M_PI/5); // changes angle degree 
  	x = x+3*radius2*cos(theta); // creates x point 
  	y = y+3*radius2*sin(theta); // creates y point

  	drawSpiral( x, y, radius1, radius2, theta ); // recursive call to create spiral shape 
  	drawSpiral( x, y, radius2, 0.25, 0 );
}

void shrinkingSquares(double xc, double yc, double length) // draws shrinkingSquare fractal 
{
	gfx_color(255, 255, 255); 
	
	if (length < 2 ) {
		return; 
	}
	
	drawSquare(xc, yc, length);  // creates basic square shape 

	// recursive calls to create embedded squares in same formation as show in example on course website 
	shrinkingSquares(xc-length/2, yc-length/2, length*45/100 ); 
  	shrinkingSquares(xc+length/2, yc-length/2, length*45/100 );
  	shrinkingSquares(xc-length/2, yc+length/2, length*45/100 );
  	shrinkingSquares(xc+length/2, yc+length/2, length*45/100 );
}

void spiralSquares(double xc, double yc, double length, double theta) // draws spiralSquares fractal 
{
	gfx_color(255, 255, 255); 
	
	if (xc >= 700 || xc<0){
		return; 
	}

	drawSquare(xc, yc, length); // calls square shape 
	length = 1.1*length;
  	theta = theta-(M_PI/5); 
  	xc = xc+4*length*cos(theta); // creates x coordinate spiral of square 
  	yc = yc+4*length*sin(theta); // cerates y coordinate spiral of square 

   spiralSquares( xc, yc, length, theta ); // recursive call 
 }

void circularLace(double xc, double yc, double radius) // draws circularLace fractal 
{
	gfx_color(255, 255, 255);

	if (radius <2) { 
		return; 
	}

	gfx_circle(xc, yc, radius);  // uses gfx_circle function as initial shape 

	for (double i = 0; i <= 2*M_PI*5/6; i = i+M_PI/3 ) // for loop to create circles equi-distant from one another 
  	{
    	circularLace( xc+radius*cos(i), yc+radius*sin(i), radius/3 ); // recursive call to create embedded circles 
  	} 
}


void snowflake( double x, double y, double radius, double theta ) // creates snowflake fractal shape 
{
	gfx_color(255, 255, 255); 
	double x2, y2;
	for ( int i = 0; i < 5; i++ )
	{
		
    	x2 = x+radius*cos(theta+i*2*M_PI/5); // creates x coordinate 
    	y2 = y-radius*sin(theta+i*2*M_PI/5); // creates y coordinate 
  
    	if (radius < 2 ) { 
			return; 
		}
	
		gfx_line(x, y, x2, y2);  // creates line that connects  the circular shapes 
		
		snowflake(x2, y2, radius/3, theta); // recursive call 
	}
}

void tree(double x, double y, double length, double theta ) // function that creates tree fractal shape 
{
	gfx_color(255, 255, 255); 
 	double x1, y1;

	x1 = x+length*sin(theta); // creates x coordinate 
	y1 = y-length*cos(theta); // creates y cooridnate 
	
	if ( length < 2 ) {
		return; 
	}		

	gfx_line(x, y, x1, y1); // creates line between generated points 
	
	tree( x1, y1, length/1.5, theta-M_PI/5 ); // recursive call 
	tree( x1, y1, length/1.5, theta+M_PI/5 ); // recursive call 
}

void fern(double x, double y, double length, double theta ) // function for fern fractal 
{
	double x2, y2;
 
	gfx_color( 0, 255, 0 ); // green color for fern 
	x2 = x+length*sin(theta); // creates 2nd x coordinate 
	y2 = y-length*cos(theta); // creates 2nd y coordinate 
 
	if ( length < 5 ) { 
		return; 
	}
	
	gfx_line( x, y, x2, y2 ); // creates line between the inputted point and generate point 
	
	for ( int i = 1; i <= 4; i++ )
  	{	
    	fern( x+i*length*sin(theta)/4, y-i*length*cos(theta)/4, length/3, theta+M_PI/6 ); // recursive call 
    	fern( x+i*length*sin(theta)/4, y-i*length*cos(theta)/4, length/3, theta-M_PI/6 ); // recursive call 
   	}
}

void spiralOfSpirals(double x, double y, double length, double radius, double theta ) // function for spiralOfSpirals fractals 
{
	gfx_color(255, 255, 255); 
	
	if (radius>=350){
		return;
	}
	
	drawSpiral(x, y, radius, 0.5, 0); 	 // calls drawSPiral to get individual spirals that will make up greater spiral 

	radius = 1.1*radius; // radius for greater spiral (similar to drawSpiral() function 
 	theta = theta-(M_PI/5); // angle for greater spiral 
  	x = x+3*radius*cos(theta); // x coordinate for greater spiral 
  	y = y+3*radius*sin(theta); // y coordinate for greater spiral 

	spiralOfSpirals(x, y, length, radius, theta);  // recursive spiral 
}
