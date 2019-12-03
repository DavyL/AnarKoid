#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/glut.h>

//#include "math_3d.h"
#include "common.h"
#include "util.h"
#include "GLutils.h"
#include "matrixUtils.h"
//#include "draw.h"

#define DELTA_TIME 	0.01f
#define BRICKS_NUMBER 	12
#define BAR_ALTITUDE	-0.9f
#define BAR_WIDTH	0.15f
#define BAR_HEIGHT	0.025f

void square_render(int);

GLuint VBO[2];
GLuint VAO[2];

GLuint shader[2];

GLuint * shader_bricks;

GLuint * shader_scale;
GLuint * scale_location;
GLuint * shader_bar;
GLuint * shader_ball;

GLuint * ball_location;
GLuint * g_world_location;
GLuint * bar_x_pos_location;

GLuint BRICKS_VAO[16];
GLuint BRICKS_VBO[16];

GLuint BAR_VAO;
GLuint BAR_VBO;

GLuint BALL_VAO;
GLuint BALL_VBO;



int firstPass = 1; 
unsigned int previousTime = 0;


float bar_pos;

float ball_x_pos = 0.0f;
float ball_y_pos = -0.9f;

int bricks_index[BRICKS_NUMBER];

float scale = 0.0f;
float time = 0.0f;

//Speed is represented as a (lambda, theta) vector, normed lambda, angle theta in [-pi, pi]
float lambda_speed = 1.0f;
float theta_speed = M_PI/3;

int dir =1;
//Temporary variables, used for monitoring what happens
//Shall probably not be in the release version
//int refreshCount = 0;
//double radius = 10.0;
//double position = 1;		//It's used with multiplications, make sure not to set it to 0

//List of global constants
//Should they depend of the PC configuration
//hence come up with a calibration procedure, s.t. the program behaves the same on every machine ?
double speed = 0.0025;



struct screenInfo screen;

   
void keyboard(unsigned char key, int x, int y){
	switch(key){	
		case 'q' : 
			exit(0);
			break;	
	}
}

void special_keyboard(int key, int x, int y){
	switch(key){	
		case GLUT_KEY_LEFT:
			dir = -1;
			break;
		case GLUT_KEY_RIGHT:
			dir = 1;
			break;	
	}
}

void triangle_render(GLuint program, GLuint tr_VAO, GLuint location){

	glUseProgram(program);
		
	glUniform1f(location, cosf(scale));
	glBindVertexArray(tr_VAO);	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glUseProgram(0);
}

void render_n_square(int n, GLuint program, GLuint * sq_VAO, GLuint location){
	glUseProgram(program);
	//glUniform1f(scale_location[0], 0.0);
	struct Matrix4f World = new_identity_matrix();
	//World = translate_matrix(World, sinf(scale), (float)i/12, 0);
	World = scale_matrix(World, 0.25f, 0.01f, 0.0f);
	
	int i = 0;
	for(i =0; i<n; i++){
		glUniformMatrix4fv(location, 1, GL_TRUE, &World.m[0][0]);
		World = translate_matrix(World, sinf(scale), (float)i/12, 0);
		//glUniform1f(location, cosf(scale*i/n));
		glBindVertexArray(sq_VAO[i]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glUseProgram(0);
}
void display_bricks( int n, float y, float width, float height, GLuint program, GLuint * sq_VAO, GLuint location){


	glUseProgram(program);
	//glUniform1f(scale_location[0], 0.0);
	struct Matrix4f World = new_identity_matrix();
	//World = translate_matrix(World, sinf(scale), (float)i/12, 0);
	World = scale_matrix(World, width, height, 0.0f);
	
	int i = 0;
	for(i =0; i<n; i++){
		if(!(bricks_index[i] == 0)){
			//World = translate_matrix(World, 0, 0, 0);
			World = translate_matrix(World, (3.0f/2.0f)*width+ 2*((float) i)/((float) n) - 1.0f, y, 0);
			glUniformMatrix4fv(location, 1, GL_TRUE, &World.m[0][0]);
			//glUniform1f(location, cosf(scale*i/n));
			glBindVertexArray(sq_VAO[i]);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
	}
	glUseProgram(0);
}
void init_bricks( int n, float y, float width, float height, GLuint program, GLuint * sq_VAO, GLuint location){


	glUseProgram(program);
	//glUniform1f(scale_location[0], 0.0);
	struct Matrix4f World = new_identity_matrix();
	//World = translate_matrix(World, sinf(scale), (float)i/12, 0);
	World = scale_matrix(World, width, height, 0.0f);
	
	int i = 0;
	for(i =0; i<n; i++){
		bricks_index[i] = 1;
		//World = translate_matrix(World, 0, 0, 0);
		World = translate_matrix(World, (3.0f/2.0f)*width+ 2*((float) i)/((float) n) - 1.0f, y, 0);
		glUniformMatrix4fv(location, 1, GL_TRUE, &World.m[0][0]);
		//glUniform1f(location, cosf(scale*i/n));
		glBindVertexArray(sq_VAO[i]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glUseProgram(0);
}
int is_x_in_brick( float i, float n, float x, float width){
	if( (x >= 2* i/n - 1.0f - width ) && (x <= 2*i/n - 1.0f + width))
		return 1;
	return 0;
}
int is_y_in_brick(float y, float bricks_y, float height){
	if( (y >= bricks_y - height) && (y <= bricks_y + height))
	       return 1;
	return 0;	
}
int is_xy_in_bricks(int n, int * index, float x, float y, float width, float height, float bricks_height){
	//Returns the index of the brick in which (x,y) lies
	//Returns -1, if (x, y) is not in a brick
	int i = 0;
	if (is_y_in_brick( y, bricks_height, height)){
		for( i = 0; i < n; i++){
			if (index[i] && is_x_in_brick( (float) i, (float) n, x, width))
				return i;
		}
	}
	return -1;

}
void user_bar( float x, float y, float width, GLuint program, GLuint bar_VAO, GLuint location){
	
	glUseProgram(program);
	
	if(bar_pos + width >= 1.0f){
		dir = -1;
	}else if(bar_pos - width <= -1.0f){
		dir = 1;
	}
	bar_pos+= ( ( float ) dir ) * 0.01f;
	//fprintf(stdout , "time : %f", time);
	glUniform1f(location,  bar_pos);
	glBindVertexArray(bar_VAO);	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glUseProgram(0);
}
void ball_out_of_bound(){
	fprintf(stdout, "Ball is out of bounds");
	exit(0);
}
int is_x_in_bar(float ball_x, float bar_width, float bar_x){
	return is_y_in_brick(ball_x, bar_width, bar_x);
}
int is_xy_in_bar(int n, float ball_x, float ball_y, float bar_width, float bar_height, float bar_x){
	int index[1];*index = 1;
	return is_xy_in_bricks(1, index, ball_y, ball_x, bar_height, bar_width, bar_x);
}	
void display_ball(int number_of_bricks, float brick_width, float brick_height, float brick_altitude, float radius, GLuint program, GLuint ball_VAO, GLuint location){
	struct Matrix4f World = new_identity_matrix();
	//Ball's radius, 0.025f
	
	World = scale_matrix(World, radius, radius, 0.0f);
	

	
	if((ball_x_pos + radius >= 1.0) || (ball_x_pos - radius <= -1.0f)){
		theta_speed -= M_PI/2;
		lambda_speed = -lambda_speed;
	}
	if(ball_y_pos <= -1.0f)
		theta_speed += M_PI/2;
		//theta_speed = -theta_speed;
		//ball_out_of_bound();
	if(ball_y_pos >= 1.0f)
		theta_speed += M_PI/2;
		//theta_speed = -theta_speed;	

	int temp = -1;
	temp = is_xy_in_bricks(12, bricks_index, ball_x_pos, ball_y_pos, brick_width, brick_height, brick_altitude);

	if(temp != -1){
		theta_speed -= M_PI/2;
		//glDeleteVertexArrays(1, BRICKS_VAO[temp]);
		bricks_index[temp] = 0;
		fprintf(stdout, "brick number : %d was hit \n", temp);
	}else{
		if(!is_xy_in_bar(1, ball_x_pos, ball_y_pos, BAR_WIDTH, BAR_HEIGHT, bar_pos)){
			theta_speed = -theta_speed;
			fprintf(stdout, "Ball is inside the bar\n");
		}
	}

	float x_speed = lambda_speed*cosf(theta_speed);
	float y_speed = lambda_speed*sinf(theta_speed);
	
	ball_x_pos += x_speed*DELTA_TIME;
	ball_y_pos += y_speed *DELTA_TIME;
	glUseProgram(program);
	World = translate_matrix(World,  ball_x_pos, ball_y_pos, 0.0f);
	glUniformMatrix4fv(location, 1, GL_TRUE, &World.m[0][0]);
	glBindVertexArray(ball_VAO);	
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glUseProgram(0);
}

void idle_func( void );
void idle_func( void ){
		
	glClear(GL_COLOR_BUFFER_BIT);
	
	time += DELTA_TIME;	
	fprintf(stdout, "time : %f\n", time);
	triangle_render(*shader_scale, VAO[0], *scale_location);
	//render_n_square(12, *shader_bricks, BRICKS_VAO, *g_world_location);
	
	float bar_width = 0.15f;
	
	int number_of_bricks = 12;	
	float bricks_y = 0.75f;
	float bricks_width = 0.75f /12.0f;
	float bricks_height = 0.025f;

	float ball_radius = 0.025f;

	//init_bricks(number_of_bricks, bricks_y,  bricks_width,  bricks_height,  *shader_bricks, BRICKS_VAO, *g_world_location);
	
	display_bricks(BRICKS_NUMBER, bricks_y,  bricks_width,  bricks_height,  *shader_bricks, BRICKS_VAO, *g_world_location);
	user_bar(0.0f, 0.0f, BAR_WIDTH , *shader_bar, BAR_VAO, *bar_x_pos_location);
	display_ball(BRICKS_NUMBER, bricks_width, bricks_height, bricks_y, ball_radius, *shader_ball, BALL_VAO, *ball_location);
	glutSwapBuffers();

}

void init_buffers(){
	float * vertices =NULL;
	vertices = get_triangle_vertices(vertices, 0.5f, 0.5f, -0.5f, 0.5f, 0.0f, -0.5f);
	
	create_triangle_vertex_buffer(vertices, VAO, VBO);
//	create_std_rectangle_vertex_buffer();
	float * vert[12];
	create_n_std_rectangle_vertex_buffer(12,vert, &(BRICKS_VAO[0]), &(BRICKS_VBO[0]));	
	create_user_bar_buffer(0.0f, BAR_ALTITUDE, BAR_WIDTH, BAR_HEIGHT, &BAR_VAO, &BAR_VBO);

	create_n_ball_buffer(20, &BALL_VAO, &BALL_VBO);
	//create_ball_buffer( &BALL_VAO, &BALL_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void display_func(){
	float bar_width = 0.15f;
	
	int number_of_bricks = 12;	
	float bricks_y = 0.75f;
	float bricks_width = 0.75f /12.0f;
	float bricks_height = 0.025f;

	float ball_radius = 0.025f;

	init_bricks(number_of_bricks, bricks_y,  bricks_width,  bricks_height,  *shader_bricks, BRICKS_VAO, *g_world_location);
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
	glutDisplayFunc(display_func); 		
	glutKeyboardFunc(keyboard); 		
	glutSpecialFunc(special_keyboard); 		

	glewInit();

	if(!GLEW_VERSION_2_0){
		fprintf(stderr, "OpenGL 2.0 not available\n");
		return -1;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f); 			

	init_buffers();

	shader_bricks = malloc(sizeof(GLuint));
	scale_location = malloc(sizeof(GLuint));	
	g_world_location = malloc(sizeof(GLuint));	
	compile_shaders_bricks(shader_bricks, g_world_location);

	shader_scale = malloc(sizeof(GLuint));
	compile_shaders_scale(shader_scale, scale_location);

	shader_bar = malloc(sizeof(GLuint));
	bar_x_pos_location = malloc(sizeof(GLuint));
	compile_shaders_bar(shader_bar, bar_x_pos_location);

	shader_ball = malloc(sizeof(GLuint));
	ball_location = malloc(sizeof(GLuint));
	compile_shaders_ball(shader_ball, ball_location);

	glutMainLoop();					

	/* Prog shall never reach this point */

	return 0;

}
