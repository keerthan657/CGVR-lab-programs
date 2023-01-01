/*
Generic OpenGL program template
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

void display()
{
    // put drawing functionality
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex3f(0,100,0);
        glColor3f(0, 1, 0); glVertex3f(0,200,0);
        glColor3f(0, 0, 1); glVertex3f(100,150,0);
    glEnd();

    // always call glFlush() at the end of your drawing function
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    // button -> GLUT_LEFT_BUTTON | GLUT_RIGHT_BUTTON
    // state  -> GLUT_UP | GLUT_DOWN
}

void myInit()
{
    // set background color
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    // set camera
    gluOrtho2D(-WIDTH/2,WIDTH/2,-HEIGHT/2,HEIGHT/2);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Generic template");
    myInit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}