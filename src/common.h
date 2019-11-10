#ifndef COMMON_H
#define COMMON_H

/* Functions for handling OpenGL elem shall probably be set to static later on */

struct resource{
	//	BUFFER AND TEXTURE
	GLuint vertex_buffer;
	GLuint element_buffer;

	GLuint textures[2];

	//	SHADER
	
	GLuint vertex_shader, fragment_shader, program;

	struct{ 
		GLint fade_factor;
		GLint textures[2];
	}uniforms;

	struct{
		GLint position;
	}attributes;

	GLfloat fade_factor;

};

GLuint make_buffer( GLenum target, const void *buffer_data, GLsizei buffer_size);
GLuint make_texture( const char *filename );
GLuint make_shader( GLenum type, const char * filename); 

int make_resources(void);

GLuint make_program(GLuint vertex_shader, GLuint fragment_shader);

void render(void);

void show_info_log( GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);

struct screenInfo{
	unsigned short int width;
	unsigned short int height;
	unsigned short int posX;
	unsigned short int posY;
	
	unsigned short int fullScreen;

	long int time;
};

struct screenInfo getScreenInfo(struct screenInfo __screen);
void displayScreenInfo(struct screenInfo __screen);

char* filetobuf(char *file);

#endif
