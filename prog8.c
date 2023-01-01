/*
Write a program toimplement the Cohen Sutherland line clipping algorithm. Make provision to specify the input for multiple lines, window for clipping and viewport for displaying the clipped image.
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

#define TOP 1
#define BOTTOM 2
#define RIGHT 4
#define LEFT 8

#define TRUE 1
#define FALSE 0

int xmin,ymin,xmax,ymax;
int xvmin,yvmin,xvmax,yvmax;
int xglobal,yglobal;

int computeoutcode(int x, int y)
{
    int res = 0;

    if(y>ymax)
        res |= TOP;
    else if(y<ymin)
        res |= BOTTOM;
    
    if(x>xmax)
        res |= RIGHT;
    else if(x<xmin)
        res |= LEFT;
    
    return res;
}

void cohensuther(int x1, int y1, int x2, int y2)
{
    int code1 = computeoutcode(x1,y1);
    int code2 = computeoutcode(x2,y2);
    int accept = FALSE, done = FALSE;

    do {
        // if inside clipping window
        if((code1|code2) == 0)
        {
            printf("\ntrivial accept");
            // trivial accept
            accept = TRUE;
            done = TRUE;
        }
        else if((code1&code2) != 0)
        {
            printf("\ntrivial reject");
            // trivial reject
            accept = FALSE;
            done = TRUE;
        }
        else {
            int x,y;

            // take the code which is not zero
            int codeout = (code1!=0)?code1:code2;
            if(codeout & TOP)
            {
                x = x1 + (x2-x1) * (ymax-y1)/(y2-y1);
                y = ymax;
            }
            else if(codeout & BOTTOM)
            {
                x = x1 + (x2-x1) * (ymin-y1)/(y2-y1);
                y = ymin;
            }
            else if(codeout & RIGHT)
            {
                y = y1 + (y2-y1) * (xmax-x1)/(x2-x1);
                x = xmax;
            }
            else
            {
                y = y1 + (y2-y1) * (xmin-x1)/(x2-x1);
                x = xmin;
            }

            if(codeout==code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeoutcode(x1,y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeoutcode(x2,y2);
            }
        }
    } while(!done);

    if(accept)
    {
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
        cohensuther(xglobal,HEIGHT-yglobal,x,HEIGHT-y);
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
    glutCreateWindow("Cohen Sutherland line clipping");
    myInit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}