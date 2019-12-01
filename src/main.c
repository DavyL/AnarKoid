#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/glut.h>

//#include "math_3d.h"
#include "common.h"
#include "util.h"
//#include "draw.h"

void square_render(int);

GLuint VBO[2];
GLuint VAO[2];
GLuint shader_bricks;
GLuint shader_scale;
GLuint scale_location[2];

int firstPass = 1; 
unsigned int previousTime = 0;

float scale = 0.0f;

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



void add_shader(GLuint shader_program, const char * shader_file, GLenum shader_type){
	
	GLuint shader_obj = glCreateShader(shader_type);
	if(shader_obj ==0){
		fprintf(stderr, "Error while creating shader type %d.\n", shader_type);
		exit(1);
	}

	//Following code loads the source shader, can be used for loading multiple sources
	const GLchar * p[1];
	GLint length[1];	
	GLchar * shader_source = file_contents(shader_file, &length[0]);
	p[0] = shader_source;
	glShaderSource(shader_obj, 1, p, length);

	//Compiling and testing the shader
	
	glCompileShader(shader_obj);

	GLint success;
	glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &success);
	if(!success){
		GLchar info_log[1024];
		glGetShaderInfoLog(shader_obj, sizeof(info_log), NULL, info_log);
		fprintf(stderr, "Error compiling shader type %d : %s\n", shader_type, info_log);
	}

	//Attach the shader to the program
	glAttachShader(shader_program, shader_obj);

}

void compile_shaders_scale(){
	
	shader_scale = glCreateProgram();
	if(shader_scale ==0){
		fprintf(stderr, "Error while creating shader program.\n");
		exit(1);
	}
	
	add_shader(shader_scale, "src/shader.v.glsl", GL_VERTEX_SHADER);
	add_shader(shader_scale, "src/shader.f.glsl", GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar error_log[1024] = { 0};

	glLinkProgram(shader_scale);
	glGetProgramiv(shader_scale, GL_LINK_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader_scale, sizeof(error_log), NULL, error_log);
		fprintf(stderr, "Error linking shader program : %s\n", error_log);
		exit(1);
	}

	glValidateProgram(shader_scale);
	glGetProgramiv(shader_scale, GL_VALIDATE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader_scale, sizeof(error_log), NULL, error_log);
		fprintf(stderr, "Invalidshader program : %s\n", error_log);
		exit(1);
	}

	glUseProgram(shader_scale);

	scale_location[0] = glGetUniformLocation(shader_scale, "g_scale");
}


void compile_shaders_bricks(){
	
	shader_bricks = glCreateProgram();
	if(shader_bricks ==0){
		fprintf(stderr, "Error while creating shader program.\n");
		exit(1);
	}
	
	add_shader(shader_bricks, "src/shader.v.glsl", GL_VERTEX_SHADER);
	add_shader(shader_bricks, "src/sh_bricks.f.glsl", GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar error_log[1024] = { 0};

	glLinkProgram(shader_bricks);
	glGetProgramiv(shader_bricks, GL_LINK_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader_bricks, sizeof(error_log), NULL, error_log);
		fprintf(stderr, "Error linking shader program : %s\n", error_log);
		exit(1);
	}

	glValidateProgram(shader_bricks);
	glGetProgramiv(shader_bricks, GL_VALIDATE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader_bricks, sizeof(error_log), NULL, error_log);
		fprintf(stderr, "Invalidshader program : %s\n", error_log);
		exit(1);
	}

	glUseProgram(shader_bricks);

	scale_location[1] = glGetUniformLocation(shader_bricks, "g_scale");
}

   
 void Keyboard(unsigned char key, int x, int y){
	switch(key){ 
		case 'q' : exit(0); 
	}
}
//Creating the VBO for a triangle (3 vertices)
void create_triangle_vertex_buffer( float * vertices){

	//glUniform1f(scale_location, cosf(scale));

	glGenVertexArrays(1, &(VAO[0]));
	glBindVertexArray(VAO[0]);

	glGenBuffers(1, &(VBO[0]));
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);	//VBO containing an array of vertices

	//Feeding the VBO
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertices, GL_STATIC_DRAW);

	
	//glEnableVertexAttribArray(VAO[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
void create_std_rectangle_vertex_buffer(){
	float * vertices = NULL;
	vertices = get_square_vertices(vertices, 0.5, 0.5);
	
	glGenVertexArrays(1, &(VAO[1]));
	glBindVertexArray(VAO[1]);


	glGenBuffers(1, &(VBO[1]));
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);	//VBO containing an array of vertices

	//Feeding the VBO
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
}
void triangle_render(int index){

	glUseProgram(shader_scale);
	glUniform1f(scale_location[0], cosf(scale));
	glBindVertexArray(VAO[0]);	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glUseProgram(0);
}

void square_render(int index){

	scale +=0.01f;	

	glUseProgram(shader_bricks);
	glUniform1f(scale_location[1], -cosf(scale));
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glUseProgram(0);
}
void idle_func( void );
void idle_func( void ){
		
	glClear(GL_COLOR_BUFFER_BIT);

	triangle_render(0);
	square_render(1);

	//glBindVertexArray(0);	
	//We disable as we no longer immediately need the VBO
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);

	glutSwapBuffers();

}

void init_buffers(){
	float * vertices =NULL;
	vertices = get_triangle_vertices(vertices, 0.5f, 0.5f, -0.5f, 0.5f, 0.0f, -0.5f);

	create_triangle_vertex_buffer(vertices);
	create_std_rectangle_vertex_buffer();
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main(int argc, char *argv[]){
	int win; 	

		//fprintf(stdout, "%f\n", vertices[0]);

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA |GLUT_DOUBLE);
	glutInitWindowSize(500,400);
      	glutInitWindowPosition(100, 100);	
	win = glutCreateWindow("Anarkoid");		

	glutIdleFunc(idle_func);
	glutDisplayFunc(idle_func); 		
	glutKeyboardFunc(Keyboard); 		

	glewInit();

	if(!GLEW_VERSION_2_0){
		fprintf(stderr, "OpenGL 2.0 not available\n");
		return -1;
	}

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f); 			

	init_buffers();
	compile_shaders_bricks();
	compile_shaders_scale();

	glutMainLoop();					

	/* Prog shall never reach this point */

	return 0;

}
