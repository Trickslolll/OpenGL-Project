#include <GL/glut.h>
#include <iostream>

using namespace std;

void mydisplay();
void init();
void divide_3Dtriangle(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d, int m);
void triangle3D(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d);
GLfloat v[4][3] = { {-1.0,-0.58,0.0}, //0
					{1.0,-0.58,0.0},  //1
					{0.0,1.2,0.0},    //2
					{0.0,0.0,-0.33} };//3

int n;

int main(int argc, char** argv) {
	cout << "Input the number N: ";
	cin >> n;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(700, 250);
	glutCreateWindow("3D Gasket");
	glutDisplayFunc(mydisplay);

	init();

	glutMainLoop();
}

void mydisplay(void) {
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
	glColor3ub(0,0,255);
	
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

void triangle3D(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d) {
	glColor3ub(255, 0, 0);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);

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
