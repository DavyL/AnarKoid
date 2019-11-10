#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "common.h"
#include "util.h"
//#include "draw.h"

const GLfloat g_vertex_buffer_data[] = {
		-1.0f,	-1.0f,
		1.0f,	-1.0f,
		-1.0f,	1.0f,
		1.0f,	1.0f
	};
//Set the order in which they shall be read
const GLushort g_element_buffer_data[] = { 0, 1, 2, 3};

struct resource g_resources;



int firstPass = 1; 
unsigned int previousTime = 0;


//Temporary variables, used for monitoring what happens
//Shall probably not be in the release version
int refreshCount = 0;
double radius = 10.0;
double position = 1;		//It's used with multiplications, make sure not to set it to 0

//List of global constants
//Should they depend of the PC configuration
//hence come up with a calibration procedure, s.t. the program behaves the same on every machine ?
double speed = 0.0025;

struct screenInfo screen;

/*void render(void){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique
	glutSwapBuffers();
	
	if (firstPass) {
		screen = getScreenInfo(screen);
		displayScreenInfo(screen);	
		firstPass = 0;
//		drawScene();
	}

	fprintf(stdout, "refresh : \t %d \n", refreshCount++);

	//__glDrawSquare(200, 200, 50);	
	glFlush();
*/

//}
	//	BUFFER



void render(void){
	
	glUseProgram(g_resources.program);

	glUniform1f(g_resources.uniforms.fade_factor, g_resources.fade_factor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_resources.textures[0]);
	glUniform1i(g_resources.uniforms.textures[0], 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_resources.textures[1]);
	glUniform1i(g_resources.uniforms.textures[1], 1);


	glBindBuffer(GL_ARRAY_BUFFER, g_resources.vertex_buffer);
	glVertexAttribPointer(
			g_resources.attributes.position,	// attribute	
			2,					//size
			GL_FLOAT,				//type
			GL_FALSE,				//normalized
			sizeof(GLfloat)*2,			//stride
			(void*)0				//array buffer offset
			);

	glEnableVertexAttribArray(g_resources.attributes.position);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_resources.element_buffer);
	//	Display
	glDrawElements(
			GL_TRIANGLE_STRIP,	//mode
			4,			//count
			GL_UNSIGNED_SHORT,	//type
			(void*)0
		      );

	//Cleaning up
	glDisableVertexAttribArray(g_resources.attributes.position);

	//refreshing the buffers
	glutSwapBuffers();
}    
 void Keyboard(unsigned char key, int x, int y){
	switch(key){ 
		case 'q' : exit(0); 
	}
}
void idle_func( void );
void idle_func( void ){
	
	int milliseconds = glutGet(GLUT_ELAPSED_TIME);
	g_resources.fade_factor = sinf((float)milliseconds * 0.001f) * 0.5f + 0.5f;
	glutPostRedisplay();/*	unsigned int deltaTime = 0;

	deltaTime = glutGet(GLUT_ELAPSED_TIME) - previousTime;	
	if(deltaTime){				//Making sure that some time has elapsed, otherwise the following is pointless

		previousTime+= deltaTime;

		position *=(1 + (double) deltaTime * speed);

		if(position >= screen.height)
		       position = 1;			//Out of screen, returning to bottom

		//radius *= (1+deltaTime);
		//radius =  radius + radius * (double) deltaTime * speed;
		fprintf(stdout, "deltaTime : %d\t, position : \t %f, elapsedTime : \t %d, \n previousTime : \t %d \n",deltaTime, position, glutGet(GLUT_ELAPSED_TIME), previousTime);
	}
		__glDrawSquare(200, (int)position, 40);
		glFlush();	
*/
}


int main(int argc, char *argv[]){
	int win; 	
		
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGB |GLUT_DOUBLE);
	glutInitWindowSize(500,400);  
	win = glutCreateWindow("Anarkoid");

	glClearColor(0.9, 0.9, 0.2, 0); 	
	gluOrtho2D(0,600,0,600);			

	glutIdleFunc(&idle_func);
	glutDisplayFunc(&render); 		
	glutKeyboardFunc(Keyboard); 		

	glewInit();

	if(!GLEW_VERSION_2_0){
		fprintf(stderr, "OpenGL 2.0 not available\n");
		return -1;
	}
	if(!make_resources()){
		fprintf(stderr, "Failed to load resources.\n");
		return -1;
	}

	glutMainLoop();					

	/* Prog shall never reach this point */

	return 0;

}
