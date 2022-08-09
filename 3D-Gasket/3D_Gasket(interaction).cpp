#include <GL/glut.h>
#include <iostream>

using namespace std;

void idle();
void display();
void display3D();
void init();
void triangle(GLfloat* a, GLfloat* b, GLfloat* c);
void triangle3D(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d);
void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m);
void divide_3Dtriangle(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d, int m);
void gasket2D(int m);
void mymouse(int btn, int state, int x, int y);
void mykey(unsigned char key, int x, int y);
void mymenu(int id);
void sub_gasket(int id);
void sub_level(int id);
void createmenu();
GLfloat v[4][3] = { {-1.0,-0.58,0.0}, //0
					{1.0,-0.58,0.0},  //1
					{0.0,1.2,0.0},    //2
					{0.0,0.0,-0.33} };

int n = 1;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 250);
	glutCreateWindow("Pop Menu");
	glutKeyboardFunc(mykey);
	createmenu();
	glutDisplayFunc(idle);
	init();
	glutMainLoop();
}

void idle(){}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	gasket2D(n);
	glEnd();
	glFlush();
	
}

void display3D() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_3Dtriangle(v[0], v[1], v[2], v[3], n);
	glEnd();
	glFlush();
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3ub(0,0,0);
	
}

void triangle(GLfloat* a, GLfloat* b, GLfloat* c) {
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void triangle3D(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d) {
	/*glColor3ub(255, 0, 0);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);*/

	glColor3ub(255, 0, 0);
	glVertex3fv(d);
	glVertex3fv(c);
	glVertex3fv(b);


	glColor3ub(0, 255, 0);
	glVertex3fv(a);
	glVertex3fv(d);
	glVertex3fv(b);

	glColor3ub(0, 0, 255);
	glVertex3fv(a);
	glVertex3fv(c);
	glVertex3fv(d);
}

void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m) {
	GLfloat v1[3], v2[3], v3[3];
	if (m > 0) {
		for (int i = 0; i < 3; i++) {
			v1[i] = (a[i] + b[i]) / 2;
			v2[i] = (a[i] + c[i]) / 2;
			v3[i] = (b[i] + c[i]) / 2;
		}
		divide_triangle(a, v1, v2, m - 1);
		divide_triangle(c, v2, v3, m - 1);
		divide_triangle(b, v3, v1, m - 1);
	}

	else triangle(a, b, c);
}

void divide_3Dtriangle(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d, int m) {
	GLfloat v1[3], v2[3], v3[3], v4[3], v5[3], v6[3];
	if (m > 0) {
		for (int i = 0; i < 3; i++) {
			v1[i] = (a[i] + b[i]) / 2;
			v2[i] = (a[i] + c[i]) / 2;
			v3[i] = (a[i] + d[i]) / 2;
			v4[i] = (b[i] + c[i]) / 2;
			v5[i] = (b[i] + d[i]) / 2;
			v6[i] = (d[i] + c[i]) / 2;
		}
		divide_3Dtriangle(a, v1, v2, v3, m - 1);
		divide_3Dtriangle(v1, b, v4, v5, m - 1);
		divide_3Dtriangle(v2, v4, c, v6, m - 1);
		divide_3Dtriangle(v3, v5, v6, d, m - 1);
	}
	else triangle3D(a, b, c, d);
}

void gasket2D(int m) {
	glColor3f(0.0, 1.0, 0.0);
	divide_triangle(v[0], v[1], v[2], m);
	glColor3f(0.0, 0.0, 1.0);
	divide_triangle(v[3], v[2], v[1], m);
	glColor3f(0.0, 0.0, 0.0);
	divide_triangle(v[0], v[3], v[1], m);
	glColor3f(1.0, 0.0, 0.0);
	divide_triangle(v[0], v[2], v[3], m);
}

void mymouse(int btn, int state, int x, int y) {
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		exit(0);
	}
}

void mykey(unsigned char key, int x, int y) {
	if (key == 'Q' || key == 'q') {
		exit(0);
	}
}

void mymenu(int id) {
	if (id == 6)
		exit(0);
}

void sub_gasket(int id) {
	if (id == 1) { //surface
		glutDisplayFunc(display);
		glutPostRedisplay();
	}
	if (id == 2) { //volume
		glutDisplayFunc(display3D);
		glutPostRedisplay();
	}
}

void sub_level(int id) {
	if (id == 3) {
		n = 2;
		glutPostRedisplay();
	}
		
	if (id == 4) {
		n = 3;
		glutPostRedisplay();
	}
	if (id == 5) {
		n = 4;
		glutPostRedisplay();
	}
}

void createmenu() {
	int gasket = glutCreateMenu(sub_gasket);
	glutAddMenuEntry("Surface Subdivision", 1);
	glutAddMenuEntry("Volume Subdivision", 2);

	int level = glutCreateMenu(sub_level);
	glutAddMenuEntry("2", 3);
	glutAddMenuEntry("3", 4);
	glutAddMenuEntry("4", 5);


	int menu_id = glutCreateMenu(mymenu);
	glutAddSubMenu("3D Gasket", gasket);
	glutAddSubMenu("Subdivision Level", level);
	glutAddMenuEntry("Exit", 6);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
