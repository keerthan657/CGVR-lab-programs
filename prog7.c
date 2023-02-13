/*
Write a program to fill any given 2D polygon using scan-line area filling algorithm.
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

typedef struct point_2d {
    int x,y;
} point;

int nPoints, m;
point points[10];

// this will hold intersection points along X axis
int intx[10];

void drawLine(int x1, int y1, int x2, int y2)
{
    for(int i=0; i<3000000; i++);

    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
}

void edgeDetect(int x1, int y1, int x2, int y2, int scanline)
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

    if(scanline>y1 && scanline<y2)
        intx[m++] = x1 + (x2-x1)*(scanline-y1)/(y2-y1);
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void scanlinefill()
{
    for(int y=0; y<500; y++)
    {
        m = 0;
        for(int i=0; i<nPoints; i++)
            edgeDetect(points[i].x, points[i].y, points[(i+1)%nPoints].x, points[(i+1)%nPoints].y, y);
        
        qsort(intx, m, sizeof(int), cmpfunc);
        if(m>=2) {
            for(int i=0; i<m-1; i+=2) {
                drawLine(intx[i], y, intx[i+1], y);
                glFlush();
            }
        }
    }
}

void display()
{
    // draw polygon
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<nPoints; i++)
    {
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();

    // scan line filling
    glColor3f(0,1,0);
    scanlinefill();

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

int main(int argc, char* argv[])
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
    points[3].x = 250; points[3].y = 200;

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("scan line polygon filling");
    myInit();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
