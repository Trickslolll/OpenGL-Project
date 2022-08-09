#include <GL/glut.h>
#include <iostream>
#include <Windows.h>
#include <ctime>
#define G 9.8

using namespace std;
void reset(); // use this function to reset all condition => approximate to the def. restart program
void display();
void init();
void mymenu(int id);
void createmenu();
void polygon();
void line();
void drop();
void timer(int value);
void up();
void changedrop();
void changeup();
void shear_right();
void shear_left();

GLfloat v[4][3] = { {-0.25,1.27,0}, //0
					{0.25,1.27,0},  //1
					{0.5,0.81,0}, //2
					{-0.5,0.81,0} }; //3

GLfloat v2[4][3] = { {-0.25,1.27,0}, //0
					{0.25,1.27,0},  //1
					{0.31,1.15,0}, //2
					{-0.31,1.15,0} }; //3

double total = 0;
double t = 0.002;
float speed = 0;
float speedTemp = 0;
int dir = 1;
float boundsBack = 0.2;
float limit = 0.2;
int flag = 0;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Jump&Drop");
	createmenu();
	init();
	glutDisplayFunc(display);
	glutTimerFunc(2, timer, 0);
	
	glutMainLoop();
	return 0;
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(2, timer, 0);
}

void reset() {
	//reset position

	v[0][0] = -0.25;
	v[0][1] = 1.27;
	v[0][2] = 0;

	v[1][0] = 0.25;
	v[1][1] = 1.27;
	v[1][2] = 0;

	v[2][0] = 0.5;
	v[2][1] = 0.81;
	v[2][2] = 0;

	v[3][0] = -0.5;
	v[3][1] = 0.81;
	v[3][2] = 0;

	speed = 0;
	dir = 1;
	boundsBack = 0.2;
	limit = 0.3;
	flag = 0;
	glutPostRedisplay();
}

void changedrop() { //dir = 3
	float offsetX = speedTemp *t + 0.5 * G * t *t;
	float offsetY = speedTemp *t + 0.5 * G * t *t;
	v[0][0] -= offsetX;
	v[1][0] += offsetX;
	v[2][0] += offsetX;
	v[3][0] -= offsetX;

	v[0][1] -= offsetY;
	v[1][1] -= offsetY;
	
	speedTemp += G * t;
	if ((v[1][1] - v[3][1]) <= boundsBack) {
		boundsBack += 0.05;
		dir = 4;
	}
}

void drop() { //dir = 1;
	float offset = speed * t + 0.5 * G * t * t;
	v[0][1] -= offset;
	v[1][1] -= offset;
	v[2][1] -= offset;
	v[3][1] -= offset;

	speed += G * t;
	if (v[3][1] <= -1.7) {
		dir = 3;
		if (speed <= 1.8) {  //stop the jump
			dir = 2;
		}
	}
}

void up() { //dir = 0
	float offset = (0.6)*speed * t - 0.5 * G * t * t;
	v[0][1] += offset;
	v[1][1] += offset;
	v[2][1] += offset;
	v[3][1] += offset;
  
	speed -= G * t;
	if (speed <= 0.1) {
		dir = true;
	}
}

void changeup() {
	float offsetX = speedTemp * t - 0.5 * G * t * t;
	float offsetY = speedTemp * t - 0.5 * G * t * t;
	v[0][0] += offsetX;
	v[1][0] -= offsetX;
	v[2][0] -= offsetX;
	v[3][0] += offsetX;

	v[0][1] += offsetY;
	v[1][1] += offsetY;

	speedTemp -= G * t;
	if (speedTemp <= 0.1) {
		dir = 0;
	}
}

void polygon(){
	glBegin(GL_POLYGON);
	glColor3ub(255, 209, 60);
	glVertex2fv(v[0]);
	glVertex2fv(v[1]);
	glVertex2fv(v[2]);
	glVertex2fv(v[3]);
	glEnd();
}

void polygonDark() {
	glBegin(GL_POLYGON);
	glColor3ub(224, 202, 164);
	glVertex2fv(v2[0]);
	glVertex2fv(v2[1]);
	glVertex2fv(v2[2]);
	glVertex2fv(v2[3]);
	glEnd();
}

void line() {
	glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
	glVertex2f(-100, -1.7);
	glVertex2f(100, -1.7);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	line();
	polygon();

	if (dir == 1) { //drop
		drop();
	}
	else if (dir == 3) { //change shape (small)
		changedrop();
	}
	else if (dir == 4) { //change shape (big)
		changeup();
	}
	else if(dir == 0) { //right
		shear_right();
	}
	else if (dir == 5) {
		shear_left();
	}
	else if (dir == 2) {
		v[0][0] = -0.25;
		v[1][0] = 0.25;
	}

	glPopMatrix();
	glutSwapBuffers();
}

void shear_right() {
	
	if (limit > 0.05) {
		v[0][0] += limit;
		v[1][0] += limit;
		dir = 5;
		limit -= 0.03;
	}
	else {
		dir = 2; // set to idle
	}
	if (flag == 1) {
		v[0][0] += limit;
		v[1][0] += limit;
	}
	Sleep(100);
}

void shear_left() {
	flag = 1;
	if (limit > 0.05) {
		v[0][0] -=  2*limit;
		v[1][0] -=  2*limit;
	}
	dir = 0;
	Sleep(100);
}

void init() {
	glClearColor(1, 1, 1, 1);
	glColor3ub(0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2, 2, -2, 2);
}

void mymenu(int id) {
	if (id == 1)
		exit(0);
	else if (id == 0) {
		reset();
	}
}

void createmenu() {
	int menu_id = glutCreateMenu(mymenu);
	
	glutAddMenuEntry("Restart the program",0);
	glutAddMenuEntry("Exit", 1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
