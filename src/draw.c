#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "draw.h"

void __glDrawSquare(unsigned int basePointX, unsigned int basePointY,
	       	unsigned int width){	//Draws a square with side of size width 
					//with a basepoint (bottom-left) at coords (basePointX, basePoint Y)
	glBegin(GL_POLYGON);
	glVertex2i(basePointX, basePointY);
	glVertex2i(basePointX + width, basePointY);
	glVertex2i(basePointX + width, basePointY + width);
	glVertex2i(basePointX, basePointY + width);
	glEnd();

}


