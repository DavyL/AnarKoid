#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "common.h"
#include "draw.h"

int firstPass = 1; 
int time = 0;

struct screenInfo screen;

void Refresh(void){
	glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique

	if (firstPass) {
		screen = getScreenInfo(screen);
		displayScreenInfo(screen);	
		firstPass = 0;
	}

	fprintf(stdout, "time : \t %d \n", time++);

	__glDrawSquare(200, 200, 50+time);	
	glFlush(); 			
}
void Keyboard(unsigned char key, int x, int y){
	switch(key){ 
		case 'q' : exit(0); 
	}

	Refresh();
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

	glutMainLoop();					

	/* Prog shall never reach this point */

	return 0;

}
