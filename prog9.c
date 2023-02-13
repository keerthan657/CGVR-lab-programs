/*
Write a program toimplement the Liang barsky line clipping algorithm. Make provision to specify the input for multiple lines, window for clipping and viewport for displaying the clipped image.
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

#define TRUE 1
#define FALSE 0

int xmin,ymin,xmax,ymax;
int xvmin,yvmin,xvmax,yvmax;
int xglobal,yglobal;

int cliptest(int p, int q, float *t1, float *t2)
{
    float t = (float)q/p;

    if(p<0)
    {
        if(t > *t1) *t1=t;
        if(t > *t2) return FALSE;
    }
    else if(p>0)
    {
        if(t < *t2) *t2=t;
        if(t < *t1) return FALSE;
    }
    else
        if(p==0)
            if(q<0) return FALSE;
    
    return TRUE;
}

void liangbarsky(int x1, int y1, int x2, int y2)
{
    // calculate dx and dy
    int dx = x2-x1, dy = y2-y1;
    // set initial t values (t1=t_entry, t2=t_exit)
    float t1=0.0, t2=1.0;
    // test clipping wrt all 4 sides
    if(cliptest(-dx, x1-xmin, &t1, &t2))
    if(cliptest( dx, xmax-x1, &t1, &t2))
    if(cliptest(-dy, y1-xmin, &t1, &t2))
    if(cliptest( dy, ymax-y1, &t1, &t2))
    {
        // calculate new coordinates
        if(t2<1.0)
        {
            x2 = x1 + t2 * dx;
            y2 = y1 + t2 * dy;
        }
        if(t1>0.0)
        {
            x1 = x1 + t1 * dx;
            y1 = y1 + t1 * dy;
        }

        // plot on viewport
        float sx = (xvmax-xvmin)/(xmax-xmin);
        float sy = (yvmax-yvmin)/(ymax-ymin);

        int x1_new = xvmin + (x1-xmin)*sx;
        int y1_new = yvmin + (y1-ymin)*sy;
        int x2_new = xvmin + (x2-xmin)*sx;
        int y2_new = yvmin + (y2-ymin)*sy;

        glColor3f(0,1,0);
        glBegin(GL_LINES);
            glVertex2d(x1_new,y1_new);
            glVertex2d(x2_new,y2_new);
        glEnd();
        glFlush();
    }
}

void display()
{
    // draw window
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    // draw viewport
    glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin, yvmin);
        glVertex2f(xvmax, yvmin);
        glVertex2f(xvmax, yvmax);
        glVertex2f(xvmin, yvmax);
    glEnd();

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        xglobal = x;
        yglobal = y;
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        glColor3f(1,0,0);
        glBegin(GL_LINES);
            glVertex2f(xglobal,HEIGHT-yglobal);
            glVertex2f(x,HEIGHT-y);
        glEnd();

        // apply clipping using cohen sutherland algorithm
        liangbarsky(xglobal,HEIGHT-yglobal,x,HEIGHT-y);
        glFlush();
    }
}

void myInit()
{
    // set background color
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    // set camera
    gluOrtho2D(0,500,0,500);
}

int main(int argc, char *argv[])
{
    // // input window coordinates - ex: -200 -200 0 0
    // printf("\nEnter window coordinates (xmin ymin xmax ymax) - ");
    // scanf("%d%d%d%d", &xmin, &ymin, &xmax, &ymax);
    // // input viewport coordinates - ex: 0 0 200 200
    // printf("\nEnter viewport coordinates (xmin ymin xmax ymax) - ");
    // scanf("%d%d%d%d", &xvmin, &yvmin, &xvmax, &yvmax);

    xmin = ymin = 100;
    xmax = ymax = 200;
    xvmin = yvmin = 300;
    xvmax = yvmax = 400;

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Liang Barsky line clipping");
    myInit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
