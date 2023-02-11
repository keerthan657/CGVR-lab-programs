/*
Write a program to generate a circle using Bresenham’s circle drawing. User can specify inputs through keyboard/mouse.
*/

#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

int xglobal,yglobal;

void drawPixel(int x, int y)
{
    glColor3f(1,0,0);

    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void plot8points(int xc, int yc, int x, int y)
{
    drawPixel(xc+x,yc+y);
    drawPixel(xc-x,yc+y);
    drawPixel(xc+x,yc-y);
    drawPixel(xc-x,yc-y);
    drawPixel(xc+y,yc+x);
    drawPixel(xc+y,yc-x);
    drawPixel(xc-y,yc+x);
    drawPixel(xc-y,yc-x);
}

void drawCircle(int xc, int yc, int r)
{
    // initialize variables
    int x=0, y=r;
    int incx=1, incy=-1;

    // calculate initial decision parameter
    int p = 3 - 2*r;

    // plot the circle
    while(x<y) {
        if(p<0) {
            p += 4*x + 6;
            x += incx;
        } else {
            p += 4*(x-y) + 10;
            x += incx;
            y += incy;
        }
        plot8points(xc,yc,x,y);
    }
    
    // V.V.IMP - never forget to call glFlush() at the end
    glFlush();
}

int getRadius(int x1, int y1, int x2, int y2)
{
    return (int)sqrt(float((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}

void display() {}

void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        xglobal = x - WIDTH/2;
        yglobal = HEIGHT/2 - y;
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        x = x - WIDTH/2;
        y = HEIGHT/2 - y;
        int radius = getRadius(xglobal, yglobal, x, y);
        printf("drawing circle at (%d,%d) with radius %d\n", xglobal, yglobal, radius);
        drawCircle(xglobal, yglobal, radius);
    }
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
    glutCreateWindow("Bresenham Circle Drawing");
    myInit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}