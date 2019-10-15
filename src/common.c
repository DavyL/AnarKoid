#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "common.h"

struct screenInfo getScreenInfo(struct screenInfo __screen){

	__screen.width 		= glutGet(GLUT_WINDOW_WIDTH);
	__screen.height 	= glutGet(GLUT_WINDOW_HEIGHT);
	__screen.posX 		= glutGet(GLUT_WINDOW_X);
	__screen.posY 		= glutGet(GLUT_WINDOW_Y);

	return __screen;
}
void displayScreenInfo(struct screenInfo __screen){
	fprintf(stdout, "Screen width :\t %d \n", __screen.width ); 
	fprintf(stdout, "Screen height :\t %d \n", __screen.height); 
	fprintf(stdout, "Screen X pos :\t %d \n", __screen.posX); 
	fprintf(stdout, "Screen Y pos :\t %d \n", __screen.posY); 
}


