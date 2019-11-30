#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/glut.h>

//#include "math_3d.h"
#include "common.h"
#include "util.h"
//#include "draw.h"

void square_render(void);

GLuint VBO[2];
GLuint scale_location;

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
	//	BUFFER

void triangle_render(void){

	glClear(GL_COLOR_BUFFER_BIT);

	scale +=0.01f;

	glUniform1f(scale_location, 3.14 + cosf(scale));
	
	//Activating it (there is a link w/ the shader here
	glEnableVertexAttribArray(0);

	//Binding for drawing
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	//Telling the pipeline how to interpret the data from the VBO
	//the first '0', is the index of the attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//And drawing
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//We disable as we no longer immediately need the VBO
	glDisableVertexAttribArray(1);

//	glutSwapBuffers();
}

//Creating the VBO for a triangle (3 vertices)
void create_triangle_vertex_buffer( float * vertices){

	glGenBuffers(1, &(VBO[0]));
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);	//VBO containing an array of vertices

	//Feeding the VBO
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertices, GL_STATIC_DRAW);

}
void create_std_rectangle_vertex_buffer(){
	float * vertices = NULL;
	vertices = get_square_vertices(vertices, 0, 1);

	glGenBuffers(1, &(VBO[1]));
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);	//VBO containing an array of vertices

	//Feeding the VBO
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), vertices, GL_STATIC_DRAW);

}
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

void compile_shaders(){
	
	GLuint shader_program = glCreateProgram();
	if(shader_program ==0){
		fprintf(stderr, "Error while creating shader program.\n");
		exit(1);
	}
	
	add_shader(shader_program, "src/shader.v.glsl", GL_VERTEX_SHADER);
	add_shader(shader_program, "src/shader.f.glsl", GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar error_log[1024] = { 0};

	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader_program, sizeof(error_log), NULL, error_log);
		fprintf(stderr, "Error linking shader program : %s\n", error_log);
		exit(1);
	}

	glValidateProgram(shader_program);
	glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader_program, sizeof(error_log), NULL, error_log);
		fprintf(stderr, "Invalidshader program : %s\n", error_log);
		exit(1);
	}

	glUseProgram(shader_program);

	scale_location = glGetUniformLocation(shader_program, "g_scale");
}

   
 void Keyboard(unsigned char key, int x, int y){
	switch(key){ 
		case 'q' : exit(0); 
	}
}
void idle_func( void );
void idle_func( void ){
		
	triangle_render();

	glClear(GL_COLOR_BUFFER_BIT);
	
	scale +=0.01f;

	glUniform1f(scale_location, cosf(scale));
	
	//Activating it (there is a link w/ the shader here
	glEnableVertexAttribArray(0);

	//Binding for drawing
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

	//Telling the pipeline how to interpret the data from the VBO
	//the first '0', is the index of the attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//And drawing
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//We disable as we no longer immediately need the VBO
	glDisableVertexAttribArray(0);

	glutSwapBuffers();

}


int main(int argc, char *argv[]){
	int win; 	

	float * vertices;
	vertices = get_triangle_vertices(vertices, 0.5f, 0.5f, -0.5f, 0.5f, 0.0f, -0.5f);

	//fprintf(stdout, "%f\n", vertices[0]);

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA |GLUT_DOUBLE);
	glutInitWindowSize(500,400);
      	glutInitWindowPosition(100, 100);	
	win = glutCreateWindow("Anarkoid");		

	glutIdleFunc(idle_func);
	glutDisplayFunc(triangle_render); 		
	glutKeyboardFunc(Keyboard); 		

	glewInit();

	if(!GLEW_VERSION_2_0){
		fprintf(stderr, "OpenGL 2.0 not available\n");
		return -1;
	}

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f); 			
	create_triangle_vertex_buffer(vertices);
	create_std_rectangle_vertex_buffer();
	compile_shaders();

	glutMainLoop();					

	/* Prog shall never reach this point */

	return 0;

}
