#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "draw.h"

void __glDrawSquare(unsigned int basePointX, unsigned int basePointY,
	       	unsigned int width){	//Draws a square with side of size width 
					//with a basepoint (bottom-left) at coords (basePointX, basePoint Y)
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	glVertex2i(basePointX, basePointY);
	glVertex2i(basePointX + width, basePointY);
	glVertex2i(basePointX + width, basePointY + width);
	glVertex2i(basePointX, basePointY + width);
	glEnd();

}
void drawSquare(){

	//Specify the vertices
	const GLfloat g_vertex_buffer_data[] = {
		-1.0f,	-1.0f,
		1.0f,	-1.0f,
		-1.0f,	1.0f,
		1.0f,	1.0f
	};
	//Set the order in which they shall be read
	const GLushort g_element_buffer_data[] = { 0, 1, 2, 3};

}
