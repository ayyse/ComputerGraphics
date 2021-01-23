#include <iostream>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <math.h>


#define PI 3.141592f
#define LEFT 1
#define RIGHT 2

float theta = PI / 2.0f - 0.4f;
float phi = 0.0f;
float distance = 40.0f;
float oldX, oldY;
int motionState;
float degree = 0;
int turn = 0;


GLfloat angle = 45.0f;
int delay = 1;

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, 0);
}

void init() {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500, 500, -500, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
}

void front() 
{
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-450, -250, 0); // front face position
	glScalef(0.01, 0.3, 0.85);
	glutWireCube(600);
	glPopMatrix();
}

void back()
{
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(450, -250, 0); // back face position
	glScalef(0.01, 0.3, 0.85); // 
	glutWireCube(600);
	glPopMatrix();
}

void right()
{
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, -250, -250); // right face position
	glScalef(1.5, 0.3, 0.01);
	glutWireCube(600);
	glPopMatrix();
}

void left() 
{
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, -250, 250); //left face position
	glScalef(1.5, 0.3, 0.01);
	glutWireCube(600);
	glPopMatrix();
}


void wheel(int x, int y, int z) 
{
	float th;
	glColor3f(1, 1, 1);
	int j;
	for (j = 0; j < 10; j++)
	{
		glBegin(GL_LINES);
		for (int i = 0; i < 360; i++) {
			th = i * 3.142 / 180;
			glVertex3f(x + 100 * cos(th), y + 100 * sin(th), z + j);
		}
		glEnd();
	}
}

// line between two wheel
void wheelLine(int x, int y, int z)
{
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	// link between right and left wheels
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);
	glEnd();
}

//steering wheel line
void line(int x, int y, int z)
{
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-420, -50, 0);
	glRotatef(-5, 0, 0, 1);
	glScalef(0.0, 1.0, 0.0);
	glutWireCube(600);
	glPopMatrix();
}

void steering(int x, int y, int z)
{
	float th;
	glColor3f(1, 1, 1);

	int j;
	for (j = 0; j < 10; j++)
	{
		glBegin(GL_LINES);
		for (int i = 0; i < 360; i++) {
			th = i * 3.142 / 180;
			glVertex3f(x + 100 * cos(th), y + 100 * sin(th), z + j);
		}
		glEnd();
	}
}

void streeringLine()
{
	glColor3f(1, 1, 1);

	// horizontal
	glPushMatrix();
	glTranslatef(-400, 250, 0);
	glRotatef(90 + turn, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.0, 1.0, 0.0); 
	glutWireCube(200); // steering diameter
	glPopMatrix();

	// vertical
	glPushMatrix();
	glTranslatef(-400, 250, 0);
	glRotatef(90 + turn, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1.0, 0.0, 0.0);
	glutWireCube(200);
	glPopMatrix();
}

void frontLines()
{
	glColor3f(1, 1, 1);

	// front left wheel
	glPushMatrix();
	glTranslatef(-450, -350, 400); // center of front left wheel
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glScalef(1.0, 0.0, 0.0);
	glutWireCube(200); // wheel diameter
	glPopMatrix();

	// front right wheel
	glPushMatrix();
	glTranslatef(-450, -350, -400); // center of front right wheel
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glScalef(1.0, 0.0, 0.0);
	glutWireCube(200); 
	glPopMatrix();

	angle += 1; // rotation speed
}

void backLines()
{
	glColor3f(1, 1, 1);

	// back left wheel
	glPushMatrix();
	glTranslatef(450, -350, 400); // center of back left wheel
	glTranslatef(0.5f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glScalef(1.0, 0.0, 0.0);
	glutWireCube(200);//çap
	glPopMatrix();

	// back right wheel
	glPushMatrix();
	glTranslatef(450, -350, -400); // center of back right wheel
	glTranslatef(0.5f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glScalef(1.0, 0.0, 0.0);
	glutWireCube(200);
	glPopMatrix();

	angle += 0.1;
}

void car() 
{
	// defined front, back, right and left functions in car function
	front();
	back();
	left();
	right();

	// rotating front wheels
	glPushMatrix();
	glRotatef(degree, 0, 1, 0);
	wheel(-450, -350, 400); // left front wheel
	wheel(-450, -350, -400); // right front wheel
	wheelLine(-460, -350, 400); // front line between two wheel
	frontLines(); //front wheel lines
	glPopMatrix();

	wheel(450, -350, 400); // left back wheel
	wheel(450, -350, -400); // right back wheel

	wheelLine(460, -350, 400); // back line between two wheel

	line(-450, 350, 0); // steering tall line
	backLines(); // back wheel lines

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	steering(0, -400, -250);
	glPopMatrix();

	streeringLine();
}


void mouse(int button, int state, int x, int y)
{
	oldX = (float)x;
	oldY = (float)y;

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			motionState = LEFT;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			motionState = RIGHT;
		}
	}
}

void mouseMotion(int x, int y)
{
	float deltaX = x - oldX;
	float deltaY = y - oldY;

	if (motionState == LEFT)
	{
		theta -= 0.01f * deltaY;
		if (theta < 0.01f) theta = 0.01f;
		else if (theta > PI / 2.0f - 0.01f) theta = PI / 2.0f - 0.01f;

		phi += 0.01f * deltaX;
		if (phi < 0) phi += 2 * PI;
		else if (phi > 2 * PI) phi -= 2 * PI;
	}
	else if (motionState == RIGHT)
	{
		distance += 0.01f * deltaY;
	}

	oldX = (float)x;
	oldY = (float)y;
	glutPostRedisplay();
}

void turnRight(void) //s
{
	glLoadIdentity();
	degree += 0.05;
	turn += 1;
}

void turnLeft(void) //a
{
	glLoadIdentity();
	degree -= 0.05;
	turn -= 1;
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a': turnRight(); break;
	case 's':turnLeft(); break;
	}

	glutPostRedisplay();
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float x = distance * sin(theta) * cos(phi);
	float y = distance * cos(theta);
	float z = distance * sin(theta) * sin(phi);
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// reduced the size of the car
	glScalef(0.4, 0.4, 0.4);
	car();
	glutSwapBuffers();
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Wire Car");
	init();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouse);
	glutKeyboardFunc(Keyboard);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}