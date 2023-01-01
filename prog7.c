/*
Write a program to fill any given 2D polygon using scan-line area filling algorithm.
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

struct point {
    int x,y;
};
struct point points[10];
int nPoints;

int LE[500], RE[500];

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

void edgeDetect(int x1, int y1, int x2, int y2)
{
    if(y2<y1)
    {
        int temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    float m;
    if(y2-y1 == 0)
        m = x2-x1;
    else
        m = (x2-x1)/(y2-y1);
    int x = x1;
    for(int y=y1; y<=y2; y++)
    {
        if(x<LE[y])
            LE[y] = x;
        if(x>RE[y])
            RE[y] = x;
        x += m;
    }
}

void display()
{
    // draw polygon
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<nPoints; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();

    // scan line filling
    glColor3f(0,1,0);
    for(int i=0; i<500; i++)
    {
        LE[i] = 500;
        RE[i] = 0;
    }
    for(int i=0; i<nPoints; i++)
        edgeDetect(points[i].x, points[i].y, points[(i+1)%nPoints].x, points[(i+1)%nPoints].y);
    for(int y=0; y<500; y++)
        if(LE[y] <= RE[y])
            for(int x=LE[y]; x<=RE[y]; x++)
            {
                drawPixel(x,y);
                glFlush();
            }

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
    // printf("\nEnter number of points - ");
    // scanf("%d", &nPoints);
    // printf("\nEnter all points -\n");
    // for(int i=0; i<nPoints; i++)
    //     scanf("%d%d", &points[i].x, &points[i].y);
    
    nPoints = 4;
    points[0].x = 100; points[0].y = 250;
    points[1].x = 250; points[1].y = 100;
    points[2].x = 400; points[2].y = 250;
    points[3].x = 250; points[3].y = 400;

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Scan line polygon fill");
    myInit();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}