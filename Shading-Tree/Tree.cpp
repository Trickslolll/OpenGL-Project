#include <GL/glut.h>
#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;
void display();
void init();
void mymenu(int id);
void createmenu();
void star();
void cone();
void cone1();
void cone2();
void cylinder();
void shading1();
void shading2();
void shadingDisable1();
void shadingDisable2();
void reset();

GLfloat diffuse0[] = { 0.0, 0.9, 0.0, 1.0 };
GLfloat ambient0[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat specular0[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat light0_pos[] = { 3.0, 2.0, 3,0, 1.0 };

GLfloat diffuse1[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat ambient1[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat specular1[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat light1_pos[] = { -3.0, 2.0, 3,0, 1.0 };

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Xmas Tree");
	createmenu();
	init();
	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
}

void star() {
	glPushMatrix();
	glLoadIdentity();
	GLfloat m = 0.1f;
	GLfloat Pi = 3.14159;
	GLfloat a = m / sqrt(2 * (1 - cos(72 * Pi / 180)));
	GLfloat bx = a * cos(18 * Pi / 180);
	GLfloat by = a * sin(18 * Pi / 180);
	GLfloat cx = a * cos(54 * Pi / 180);
	GLfloat cy = -a * sin(54 * Pi / 180);
	GLfloat mid[3] = { 0,(cy + by) / 2 -0.02 +0.24 ,0 };
	GLfloat point[5][3] = { {0,a,0},{cx,cy,0},{-bx,by,0},{bx,by,0},{-cx,cy,0} }; //ACEBD
	for (int i = 0; i < 5; i++) {
		point[i][1] += 0.24;
	}
	glBegin(GL_TRIANGLES);
		glVertex3fv(point[0]);
		glVertex3fv(mid);
		glVertex3fv(point[4]);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3fv(point[0]);
		glVertex3fv(mid);
		glVertex3fv(point[1]);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3fv(point[2]);
		glVertex3fv(mid);
		glVertex3fv(point[3]);
	glEnd();

	glPopMatrix();
}

void cone() {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, -0.2, 0);
	glRotated(180, 0, 1, 1);
	glutSolidCone(0.27, 0.4, 16, 16);
	glTranslatef(0, 0.2, 0);
	glPopMatrix();
}

void cone1() {
	
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0,-0.4,0);
	glRotated(180, 0, 1, 1);
	glutSolidCone(0.35, 0.4, 16, 16);
	glTranslatef(0, 0.4, 0);
	
	glPopMatrix();
}

void cone2() {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, -0.6, 0);
	glRotated(180, 0, 1, 1);
	glutSolidCone(0.4, 0.4, 16, 16);
	glTranslatef(0, 0.6, 0);
	
	glPopMatrix();
}

void cylinder() {
	glPushMatrix();
	glLoadIdentity();
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	glTranslatef(0, -0.8, 0);
	glRotatef(180.0f, 0.0f, 1.0f, 1.0f);
	gluCylinder(quadratic, 0.1f, 0.1f, 0.2f, 16, 16);
	glTranslatef(0, 0.8, 0);
	glPopMatrix();
}

void shading1() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
}

void shading2() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
}

void shadingDisable1() {
	glDisable(GL_LIGHT0);
}
void shadingDisable2() {
	glDisable(GL_LIGHT1);
}

void reset() {
	glDisable(GL_LIGHTING);
	display();
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 165, 0);
	cone2();
	cone1();
	cone();
	glColor3ub(139, 69, 19);
	cylinder();
	glColor3ub(230, 230, 0);
	star();
	glutSwapBuffers();
}

void init() {
	glClearColor(1, 1, 1, 1);
	glColor3ub(0, 0 , 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-2, 2, -2, 2);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}

void mymenu(int id) {
	switch (id){
	case 1:
		exit(0);
		break;
	case 0:
		shading1();
		glutPostRedisplay();
		break;
	case 2:
		shading2();
		glutPostRedisplay();
		break;
	case 3:
		shadingDisable1();
		glutPostRedisplay();
		break;
	case 4:
		shadingDisable2();
		glutPostRedisplay();
		break;
	case 5:
		reset();
		break;
	default:
		break;
	}
}

void createmenu() {
	int menu_id = glutCreateMenu(mymenu);
	
	glutAddMenuEntry("Shading1(Green)",0);
	glutAddMenuEntry("Shading2(Red)", 2);
	glutAddMenuEntry("ShadingDisable1", 3);
	glutAddMenuEntry("ShadingDisable2", 4);
	glutAddMenuEntry("Reset to default", 5);
	glutAddMenuEntry("Exit", 1);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
