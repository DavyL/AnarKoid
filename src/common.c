#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "common.h"
#include "util.h"

float * get_square_vertices(float * vertices, float center, float width){

	if(vertices !=NULL)
		free(vertices);

	vertices = calloc(12, sizeof(float));
	vertices[0] = 	center - width;	vertices[1] = 	center - width;
	vertices[3] =   center - width;	vertices[4] =  	center + width;
	vertices[6] = 	center + width;	vertices[7] = 	center - width;
	vertices[9] = 	center + width;	vertices[10] =   center + width;

	return vertices;
}
float * get_triangle_vertices(float * vertices,float x1, float y1, float x2, float y2, float x3, float y3){

	if(vertices !=NULL)
		free(vertices);

	vertices = calloc(9, sizeof(float));
	vertices[0] = 	x1;	vertices[1] =  y1;
	vertices[3] =   x2;	vertices[4] =  y2;
	vertices[6] = 	x3;	vertices[7] = y3;

	return vertices;
}


void show_info_log( GLuint object, PFNGLGETSHADERIVPROC glGet_iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog){
	GLint log_length;
	char * log;

	glGet_iv(object, GL_INFO_LOG_LENGTH, &log_length);
	log = malloc(log_length);

	glGet__InfoLog(object, log_length, NULL, log);
	
	fprintf(stderr, "%s", log);
	
	free(log);

}
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

/* A simple function that will read a file into an allocated char pointer buffer */
char* filetobuf(char *file)
{
    FILE *fptr;
    long length;
    char *buf;

    fptr = fopen(file, "rb"); /* Open file for reading */
    if (!fptr) /* Return NULL on failure */
        return NULL;
    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
    fclose(fptr); /* Close the file */
    buf[length] = 0; /* Null terminator */

    return buf; /* Return the buffer */
}


