#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "common.h"
#include "draw.h"

int firstPass = 1; 
unsigned int previousTime = 0;


//Temporary variables, used for monitoring what happens
//Shall probably not be in the release version
int refreshCount = 0;
unsigned int radius = 10;

struct screenInfo screen;

void Refresh(void){
	glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique

	if (firstPass) {
		screen = getScreenInfo(screen);
		displayScreenInfo(screen);	
		firstPass = 0;
	}

	fprintf(stdout, "refresh : \t %d \n", refreshCount++);

	//__glDrawSquare(200, 200, 50);	
	glFlush(); 			
}
void Keyboard(unsigned char key, int x, int y){
	switch(key){ 
		case 'q' : exit(0); 
	}

	Refresh();
}
void idleFunc( void );
void idleFunc( void ){

	unsigned int deltaTime = 0;

	fprintf(stdout, "radius when entering : \t %d \n", radius);

	deltaTime = glutGet(GLUT_ELAPSED_TIME) - previousTime;	
	if(deltaTime){
		previousTime+= deltaTime;
			
		//radius *= (1+deltaTime);
		radius = radius + radius * (10/100)*deltaTime;
		fprintf(stdout, "deltaTime : %d\t, Radius : \t %d, elapsedTime : \t %d, \n previousTime : \t %d \n",deltaTime, radius, glutGet(GLUT_ELAPSED_TIME), previousTime);
		__glDrawSquare(200, 200, radius);
		glFlush();
	}	
}

int main(int argc, char *argv[]){
	int win; 		
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500,400);  
	win = glutCreateWindow("Anarkoid");

	glClearColor(0.9, 0.9, 0.2, 0); 	
	gluOrtho2D(0,600,0,600);			

	glutDisplayFunc(Refresh); 		
	glutKeyboardFunc(Keyboard); 		

	glutIdleFunc(idleFunc);

	glutMainLoop();					

	/* Prog shall never reach this point */

	return 0;

}
