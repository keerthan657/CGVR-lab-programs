/*
Write a program to recursively subdivides a tetrahedron to form 3D Sierpinski gasket. The number of recursive steps is to be specified at execution time.
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

int niter;
struct point {
    int x,y,z;
} v1,v2,v3,v4;

struct point findMid(struct point v1, struct point v2)
{
    struct point res;
    res.x = (v1.x+v2.x)/2;
    res.y = (v1.y+v2.y)/2;
    res.z = (v1.z+v2.z)/2;
    return res;
}

void drawTriangle(struct point v1, struct point v2, struct point v3)
{
    glBegin(GL_POLYGON);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
}

void drawGasket(struct point v1, struct point v2, struct point v3, struct point v4)
{
    // put seperate color for each face
    glColor3f(1,0,0);
    drawTriangle(v1,v2,v3);
    glColor3f(0,1,0);
    drawTriangle(v1,v3,v4);
    glColor3f(0,0,1);
    drawTriangle(v1,v2,v4);
    glColor3f(1,0.3,0);
    drawTriangle(v2,v3,v4);
}

void divideGasket(struct point v1, struct point v2, struct point v3, struct point v4, int niter)
{
    if(niter>0)
    {
        // calculate midpoints
        struct point m12 = findMid(v1,v2);
        struct point m13 = findMid(v1,v3);
        struct point m14 = findMid(v1,v4);
        struct point m23 = findMid(v2,v3);
        struct point m24 = findMid(v2,v4);
        struct point m34 = findMid(v3,v4);
        
        // draw sub-gaskets
        divideGasket(v1,m12,m13,m14,niter-1);
        divideGasket(v2,m12,m23,m24,niter-1);
        divideGasket(v3,m23,m34,m13,niter-1);
        divideGasket(v4,m14,m34,m24,niter-1);
    } else {
        drawGasket(v1,v2,v3,v4);
    }
}

void display()
{
    // recursive call for 'niter' iterations
    divideGasket(v1, v2, v3, v4, niter);

    // always call glFlush() at the end of your drawing function
    glFlush();
}

void myInit()
{
    // set background color
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    // set camera (3D space)
    glOrtho(-250,250,-250,250,-250,250);
}

int main(int argc, char *argv[])
{
    printf("\nEnter number of subdivisions - ");
    scanf("%d", &niter);

    // specify coordinates of vertices
    v1.x=-150;v1.y=-150;v1.z=+150;
    v2.x=+150;v2.y=-150;v2.z=+150;
    v3.x=0;v3.y=+150;v3.z=+150;
    v4.x=0;v4.y=0;v4.z=-100;

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("3D Sierpinski Gasket");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}