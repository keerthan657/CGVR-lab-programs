/*
Write a program to implement the Cohen-Hodgeman polygon clipping algorithm. Make provision to specify the input polygon and window for clipping.
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

int xmin,ymin,xmax,ymax;

struct point {
    int x,y;
};
struct point points[30];
int nPoints;

int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int num = (x1*y2 - y1*x2) * (x3-x4) - (x1-x2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int num = (x1*y2 - y1*x2) * (y3-y4) - (y1-y2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

void clip(int x1, int y1, int x2, int y2)
{
    // temporary result array
    struct point new_points[30];
    int new_nPoints = 0;

    // for each edge of polygon, check if it needs clipping
    for(int i=0; i<nPoints; i++)
    {
        struct point p1 = points[i], p2 = points[(i+1)%nPoints];

        // calculate pos of 1st point
        int pos1 = (x2-x1)*(p1.y-y1)-(y2-y1)*(p1.x-x1);
        // calculate pos of 2nd point
        int pos2 = (x2-x1)*(p2.y-y1)-(y2-y1)*(p2.x-x1);

        // case 1: both points are inside
        if(pos1>=0 && pos2>=0)
        {
            // add 2nd point to temp array
            new_points[new_nPoints].x = p2.x;
            new_points[new_nPoints].y = p2.y;
            new_nPoints++;
        }
        // case 2: only 1st point is outside
        else if(pos1<0 && pos2>=0)
        {
            // add intersection point and 2nd point to temp array
            new_points[new_nPoints].x = x_intersect(x1,y1,x2,y2,p1.x,p1.y,p2.x,p2.y);
            new_points[new_nPoints].y = y_intersect(x1,y1,x2,y2,p1.x,p1.y,p2.x,p2.y);
            new_nPoints++;

            new_points[new_nPoints].x = p2.x;
            new_points[new_nPoints].y = p2.y;
            new_nPoints++;
        }
        // case 3: only 2nd point is outside
        else if(pos1>=0 && pos2<0)
        {
            // add intersection point to temp array
            new_points[new_nPoints].x = x_intersect(x1,y1,x2,y2,p1.x,p1.y,p2.x,p2.y);
            new_points[new_nPoints].y = y_intersect(x1,y1,x2,y2,p1.x,p1.y,p2.x,p2.y);
            new_nPoints++;
        }
        // case 4: both points are outside
        else
        {
            // no points are added
        }
    }

    // copy temp array to original array
    nPoints = new_nPoints;
    for(int i=0; i<nPoints; i++)
    {
        points[i].x = new_points[i].x;
        points[i].y = new_points[i].y;
    }
}

void cohenhodgeman()
{
    // do clipping for every edge of clipping window
    clip(xmin, ymin, xmax, ymin);
    clip(xmax, ymin, xmax, ymax);
    clip(xmax, ymax, xmin, ymax);
    clip(xmin, ymax, xmin, ymin);
    
    // draw the clipped polygon
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    for(int i=0; i<nPoints; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();

    glFlush();
}

void display()
{
    // draw clipping window
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    // draw original polygon
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<nPoints; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();

    // draw clipped polygon
    cohenhodgeman();

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
    xmin = ymin = 100;
    xmax = ymax = 300;

    nPoints = 4;
    points[0].x = 120; points[0].y = 120;
    points[1].x = 280; points[1].y = 70;
    points[2].x = 250; points[2].y = 350;
    points[3].x = 150; points[3].y = 200;

    // nPoints = 3;
    // points[0].x =  80; points[0].y = 270;
    // points[1].x = 150; points[1].y = 400;
    // points[2].x = 300; points[2].y = 200;
    
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Cohen Hodgeman polygon clipping");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}