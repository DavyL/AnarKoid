#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "common.h"
#include "util.h"

extern const GLfloat g_vertex_buffer_data[8];

extern const GLushort g_element_buffer_data[4];

extern struct resource g_resources;

GLuint make_buffer( GLenum target, const void *buffer_data, GLsizei buffer_size){
	
	GLuint buffer;
	
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);	
	
	//Available flags instead of STATIC : DYNAMIC, STREAM 
	//Sorted by acces speed increasing order

	//Available flags instead of DRAW (GPU pref):
	//READ Buffer will be primarily read by CPU
	//COPY will be read by both CPU and GPU (no pref)

	return buffer;
}
	//	TEXTURE

GLuint make_texture( const char *filename ){
	
	GLuint texture;
	
	int width;
	int height;

	void * pixels = read_tga(filename, &width, &height);

	if(!pixels)
		return 0;

	//	CREATING AND BINDING THE TEXTURE
	
	glGenTextures(1, &texture);
	glBindTexture( GL_TEXTURE_2D, texture);

	//	SETTING PARAMETERS FOR THE TEXTURE

	//GL_MIN/MAG controls when the sample is done in-between 2 points
	//GL_LINEAR tells the GPU to interpolate linearly between the four surrounding points (it's smooth)
	//GL_NEAREST tells the GPU to consider that the evaluated value is the closest one
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//GL_CLAMP  clamps out of range coordinates to [0, 1]
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);

	//	ALLOCATING THE TEXTURE
	
	//Allocate memory for a texture
	glTexImage2D(
			GL_TEXTURE_2D, 0,		//target, level of detail
			GL_RGB8,			//internal format
			width, height, 0,		//width, height, border
			GL_BGR, GL_UNSIGNED_BYTE,	//external format, type
			pixels				
		    );

	free(pixels);

	return texture;
}


	//	SHADER

GLuint make_shader( GLenum type, const char * filename){
	
	GLint length;

	GLchar * source = file_contents(filename, &length);
	GLuint shader;
	GLint shader_ok;
	
	if(!source)
		return 0;

	shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar **)&source, &length);

	free(source);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
	if(!shader_ok){
		fprintf(stderr, "Failed to compile : %s:\n", filename);
		show_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
		glDeleteShader(shader);
		
		return 0;
	}

	return shader;
}

GLuint make_program(GLuint vertex_shader, GLuint fragment_shader){
	GLint program_ok;

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	
	glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
	
	if(!program_ok){
		fprintf(stderr, "Failed to link shader program.\n");
		show_info_log(program, glGetProgramiv, glGetProgramInfoLog);
		glDeleteProgram(program);

		return 0;
	}

	return program;
}

int make_resources(void){
	
	//	VERTEX FIRST

	g_resources.vertex_buffer 
		= make_buffer( GL_ARRAY_BUFFER, g_vertex_buffer_data, sizeof(g_vertex_buffer_data) );
	
	//	THEN THE ELEM

	g_resources.element_buffer
		= make_buffer (GL_ELEMENT_ARRAY_BUFFER, g_element_buffer_data, sizeof(g_element_buffer_data) );

	//	NOW THE TEXTURE
	
	g_resources.textures[0] = make_texture("hello1.tga");
	g_resources.textures[1] = make_texture("hello2.tga");

	if(g_resources.textures[0]== 0 || g_resources.textures[1] == 0){
		fprintf(stderr, "A texture was not properly loaded.\n");
		return 0;
	}

	//	FINALLY THE SHADER
	
	g_resources.vertex_shader = make_shader( GL_VERTEX_SHADER, "src/shader.v.glsl");
	if(g_resources.vertex_shader == 0)
		return 0;

	g_resources.fragment_shader = make_shader( GL_FRAGMENT_SHADER, "src/shader.f.glsl");
	if(g_resources.fragment_shader == 0)
		return 0;

	g_resources.program = make_program(g_resources.vertex_shader, g_resources.fragment_shader);
	if(g_resources.program == 0)
		return 0;

	g_resources.uniforms.fade_factor = glGetUniformLocation( g_resources.program, "fade_factor");

	g_resources.uniforms.textures[0] = glGetUniformLocation(g_resources.program, "textures[0]");
	g_resources.uniforms.textures[1] = glGetUniformLocation(g_resources.program, "textures[1]");
	
	g_resources.attributes.position	 = glGetAttribLocation(g_resources.program, "position");

	return 1;
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


