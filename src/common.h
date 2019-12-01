#ifndef COMMON_H
#define COMMON_H

//Following is specified the maximal number of _____[] that shall be opened
/* Functions for handling OpenGL elem shall probably be set to static later on */

struct sq_resource{
	GLuint vertex_buffer;
	GLuint element_buffer;

	GLuint vertex_shader, fragment_shader, program;

	struct{
		GLint position;
	}attributes;
};


struct resource{
	//	BUFFER AND TEXTURE
	GLuint vertex_buffer;
	GLuint element_buffer;

	GLuint textures[2];

	//	SHADER
	
	GLuint vertex_shader, fragment_shader, program;

	struct{ 
		GLint fade_factor;
		GLint textures[3];
	}uniforms;

	struct{
		GLint position;
	}attributes;

	GLfloat fade_factor;

};

GLuint make_buffer( GLenum target, const void *buffer_data, GLsizei buffer_size);
GLuint make_texture( const char *filename );
GLuint make_shader( GLenum type, const char * filename); 

GLuint make_texture_square( );
int make_square_resources(float *, unsigned int *);

float * get_square_vertices(float * vertices, float xcenter, float ycenter, float width, float height);

int make_resources(void);

GLuint make_program(GLuint vertex_shader, GLuint fragment_shader);

void render(void);

void show_info_log( GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);

float * get_triangle_vertices(float * vertices,float x1, float y1, float x2, float y2, float x3, float y3);
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
