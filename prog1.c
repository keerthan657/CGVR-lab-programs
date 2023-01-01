/*
Write a program to generate a line using Bresenham’s line drawing technique. Consider slopes greater than one and slopes less than one. User must able to draw as many lines and specify inputs through keyboard/mouse.
*/

#include<stdio.h>
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

void drawLine(int x1, int y1, int x2, int y2)
{
    // initilize variables
    int x=x1, y=y1;
    int incx=1, incy=1;
    
    // calculate slope
    int dx = x2-x1, dy = y2-y1;
    
    // handle special cases if line is horizontal or vertical
    if(dx==0) { // vertical line (|)
        for(int i=0; i<=dy; i++)
            drawPixel(x1, y1+i);
    }
    if(dy==0) { // horizontal line (-)
        for(int i=0; i<=dx; i++)
            drawPixel(x1+i, y1);
    }

    // handle other quadrant lines
    if(dx<0) {
        dx = -dx;
        incx = -1;
    }
    if(dy<0) {
        dy = -dy;
        incy = -1;
    }
    
    // for line having SLOPE < 1 (NORMAL case)
    if(dy/dx < 1)
    {
        int p = 2*dy - dx;
        for(int i=0; i<dx; i++) {
            if(p<0) {
                p += 2*dy;
                x += incx;
            } else {
                p += 2*dy - 2*dx;
                x += incx;
                y += incy;
            }
            drawPixel(x,y);
        }
    }
    // for line having SLOPE > 1 (ABNORMAL case)
    // reaplce x with y, and y with x (expect for in drawPixel)
    else 
    {
        int p = 2*dx - dy;
        for(int i=0; i<dy; i++) {
            if(p<0) {
                p += 2*dx;
                y += incy;
            } else {
                p += 2*dx - 2*dy;
                y += incy;
                x += incx;
            }
            drawPixel(x,y);
        }
    }

    // V.V.IMP - never forget to call glFlush() at the end
    glFlush();
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
        printf("drawing line from (%d,%d) to (%d,%d)\n", xglobal, yglobal, x - WIDTH/2, HEIGHT/2 - y);
        drawLine(xglobal, yglobal, x - WIDTH/2, HEIGHT/2 - y);
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
    glutCreateWindow("Bresenham Line Drawing");
    myInit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}