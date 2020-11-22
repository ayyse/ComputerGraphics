#include<iostream>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

int x00;
int y00;
int xEnd;
int yEnd;

void init() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void bres()
{
    int dx = fabs(xEnd - x00), dy = fabs(yEnd - y00);
    int p = 2 * dy - dx;
    int x, y;

    if (x00 > xEnd) {
        x = xEnd;
        y = yEnd;
        xEnd = x00;
    }
    else {
        x = x00;
        y = y00;
    }
    //Stack Overflow Solution to generate a point:
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex2i(x, y);
    glEnd();

    while (x < xEnd) {
        x++;
        if (p < 0) {
            p = p + 2 * dy;
        }
        else {
            y++;
            p = p + 2 * dy - 2 * dx;
        }
        glBegin(GL_POINTS);
        glColor3f(0, 0, 0);
        glVertex2i(x, y);
        glEnd();

    }

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    bres();
    glFlush();

}

int main(int argc, char* argv[])
{
    cout << "Enter the co ordinates for 2 points: ";
    cin >> x00 >> y00 >> xEnd >> yEnd;

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Bresenham's Algo");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}