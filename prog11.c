/*
Write a program to create a house like figure and perform the following operations.
i. Rotate it about a given fixed point using OpenGL transformation functions.
ii. Reflect it about an axis y=mx+c using OpenGL transformation functions.
*/

#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500
#define R2D 180.0/3.14

struct point {
    int x,y;
};
struct point points[20];
int n;
int m,c;

int wid1, wid2;

void display1()
{
    glutSetWindow(wid1);

    // draw house figure
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<n; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();

    // do rotation - rotate 20 deg about (100,100)
    glPushMatrix();
    glTranslatef(100,100,0);
    glRotatef(20,0,0,1);
    glTranslatef(-100,-100,0);

    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<n; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();

    glPopMatrix();

    glFlush();
}

void display2()
{
    glutSetWindow(wid2);

    // draw house figure
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<n; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();

    // draw line
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex2f(0, m*0+c);
        glVertex2f(500, m*500+c);
    glEnd();

    // do reflection - about line y=mx+c
    glPushMatrix();
    glTranslatef(0,c,0);
    glRotatef(atan((float)(m))*R2D, 0, 0, 1);
    glScalef(1,-1,1);
    glRotatef(-atan((float)(m))*R2D, 0, 0, 1);
    glTranslatef(0,-c,0);
    
    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<n; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();

    glPopMatrix();
    
    glFlush();
}

void myInit()
{
    // set background
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    // set camera
    gluOrtho2D(0,WIDTH,0,HEIGHT);
}

int main(int argc, char *argv[])
{
    // printf("\nEnter slope and intercept values");
    // scanf("%d%d", &m, &c);
    m = 1;
    c = 0;

    n = 10;
    points[0].x = 100; points[0].y = 100;
    points[1].x = 300; points[1].y = 100;
    points[2].x = 300; points[2].y = 300;
    points[3].x = 200; points[3].y = 350;
    points[4].x = 100; points[4].y = 300;
    points[5].x = 100; points[5].y = 100;

    points[6].x = 220; points[6].y = 100;
    points[7].x = 220; points[7].y = 140;
    points[8].x = 180; points[8].y = 140;
    points[9].x = 180; points[9].y = 100;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    wid1 = glutCreateWindow("House rotation");
    glutDisplayFunc(display1);
    myInit();

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    wid2 = glutCreateWindow("House reflection");
    glutDisplayFunc(display2);
    myInit();

    glutMainLoop();

    return 0;
}
