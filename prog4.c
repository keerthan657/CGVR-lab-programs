/*
Design and develop C program using OpenGL libraries to create two windows: display a cylinder in one window and parallelepiped in second window
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

int wid1, wid2;

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
    plot8points(xc,yc,x,y);
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

void drawQuad(int x, int y, int width, int height)
{
    glBegin(GL_LINE_LOOP);
        glVertex2i(x,y);
        glVertex2i(x+width,y);
        glVertex2i(x+width,y+height);
        glVertex2i(x,y+height);
    glEnd();
}

void display_cylinder()
{
    glutSetWindow(wid1);

    glColor3f(1,0,0);
    int x=0,y=0,r=50;
    for(int i=100; i<150; i+=5)
        drawCircle(x,y+i,r);
    
    glFlush();
}

void display_parallelopiped()
{
    glutSetWindow(wid2);

    glColor3f(0,1,0);
    int x=-50,y=-50,w=100,h=150;
    for(int i=100; i<150; i+=5)
        drawQuad(x+i,y+i,w,h);
    glFlush();
}

void myInit()
{
    // set to PROJECTION mode
    glMatrixMode(GL_PROJECTION);

    // set background color
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    // set camera
    gluOrtho2D(-WIDTH/2,WIDTH/2,-HEIGHT/2,HEIGHT/2);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    // window 1 parameters
    glutInitWindowSize(WIDTH, HEIGHT);
    wid1 = glutCreateWindow("Cylinder");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutDisplayFunc(display_cylinder);
    myInit();
    
    // window 2 parameters
    glutInitWindowSize(WIDTH, HEIGHT);
    wid2 = glutCreateWindow("Parallelopiped");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutDisplayFunc(display_parallelopiped);
    myInit();

    glutMainLoop();
    return 0;
}