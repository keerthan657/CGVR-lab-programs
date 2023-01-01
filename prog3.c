/*
Design and develop an OpenGL application program to create two windows. Draw a rectangle of specified width and height by setting four different colors to its corners in the first window. In the second window, draw the same rectangle and spin it continuously. Use the double buffer concept
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

int wid1, wid2, tempid;
float spin = 0.0;

void display()
{
    // set window
    glutSetWindow(tempid);
    glClear(GL_COLOR_BUFFER_BIT);   // IMP - dont forget this function call

    // polygon rotation
    glPushMatrix();
    glLoadIdentity();
    glRotatef(spin, 0, 0, 1);   // rotate along Z axis (what if i rotate on all 3 axes??)

    glBegin(GL_POLYGON);
        // make sure position values are from (-1,1) only
        glColor3f(1,0,0);glVertex3f(-0.5,-0.5,0);
        glColor3f(0,1,0);glVertex3f(0.5,-0.5,0);
        glColor3f(0,0,1);glVertex3f(0.5,0.5,0);
        glColor3f(1,1,0);glVertex3f(-0.5,0.5,0);
    glEnd();

    glPopMatrix();

    // swap buffers based on window
    if(tempid==wid1) {
        glFlush();
        tempid = wid2;
    } else {
        glutSwapBuffers();
        tempid = wid1;
    }
}

void spinRect()
{
    spin += 0.5;   // this determines spinning speed
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        glutIdleFunc(spinRect);
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
        glutIdleFunc(NULL);
}

void myInit()
{
    // set MODELVIEW mode
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set perspective matrix - glOrtho(left,right,bottom,top,near,far)
    glOrtho(-1,1,-1,1,-1,1);
    
    // set background color
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    // window 1 parameters
    glutInitWindowSize(WIDTH, HEIGHT);
    wid1 = glutCreateWindow("Single Buffer");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutDisplayFunc(display);
    myInit();
    
    // window 2 parameters
    glutInitWindowSize(WIDTH, HEIGHT);
    wid2 = glutCreateWindow("Double Buffer");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutDisplayFunc(display);
    myInit();

    // set temporary to window 1
    tempid = wid1;

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}