#include "GL/glut.h"
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.1, 0.1, 0.0);
	glVertex3f(0.6, 0.1, 0.0);
	glVertex3f(0.8, 0.3, 0.0);
	glVertex3f(0.6, 0.6, 0.0);
	glVertex3f(0.1, 0.6, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glEnd();
	glFlush();
}
void init()
{
	glClearColor(0.0, 0.5, 0.2, 0.8);
}
int main(int argc, char** argv)
{
	glutCreateWindow("simple 3D");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}