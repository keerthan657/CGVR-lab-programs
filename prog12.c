/*
Write a program to create a color cube and spin it using OpenGL transformations. The output must be adjusted suitably when the window is resized or moved to a new position.
*/

#include<stdio.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500

float theta[3] = {0,0,0};
int axis = 0;

struct point {
    int x,y,z;
};

void drawPolygon(struct point points[], int a, int b, int c, int d, float red, float green, float blue)
{
    glColor3f(red,green,blue);
    glBegin(GL_POLYGON);
        glVertex3f(points[a].x, points[a].y, points[a].z);
        glVertex3f(points[b].x, points[b].y, points[b].z);
        glVertex3f(points[c].x, points[c].y, points[c].z);
        glVertex3f(points[d].x, points[d].y, points[d].z);
    glEnd();
}

void drawColorCube()
{
    // cube has 8 points & 6 faces
    struct point points[8];
    points[0].x = -100; points[0].y = -100; points[0].z = -100;
    points[1].x =  100; points[1].y = -100; points[1].z = -100;
    points[2].x =  100; points[2].y =  100; points[2].z = -100;
    points[3].x = -100; points[3].y =  100; points[3].z = -100;
    points[4].x = -100; points[4].y = -100; points[4].z =  100;
    points[5].x =  100; points[5].y = -100; points[5].z =  100;
    points[6].x =  100; points[6].y =  100; points[6].z =  100;
    points[7].x = -100; points[7].y =  100; points[7].z =  100;

    // front face
    drawPolygon(points, 4,5,6,7, 1,0,0);
    // back face
    drawPolygon(points, 0,1,2,3, 0,1,0);
    // left face
    drawPolygon(points, 0,4,7,3, 0,0,1);
    // right face
    drawPolygon(points, 1,5,6,2, 1,1,0);
    // top face
    drawPolygon(points, 7,6,2,3, 1,0,1);
    // bottom face
    drawPolygon(points, 4,5,1,0, 0,1,1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(theta[0], 1,0,0);
    glRotatef(theta[1], 0,1,0);
    glRotatef(theta[2], 0,0,1);

    // draw cube (we draw individual faces)
    drawColorCube();

    glPopMatrix();

    glFlush();
}

void spinCube()
{
    // some delay
    for(int i=0; i<10000000; i++);

    theta[axis] += 2.0;
    if(theta[axis]>360)
        theta[axis] = 0;
    
    // force redisplay of window
    glutPostRedisplay();
}

// NOTE: this function is not working properly
void reshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);

    if(w<=h)
        glOrtho(-250,250,-250*(float)h/(float)w,250*(float)h/(float)w,-250,250);
    else
        glOrtho(-250*(float)h/(float)w,250*(float)h/(float)w,-250,250,-250,250);
    
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        axis = 0;
    if(button==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
        axis = 1;
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
        axis = 2;
}

void myInit()
{
    // set background
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // set camera
    glOrtho(-250,250,-250,250,-250,250);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("RGB Tesseract");
    glutDisplayFunc(display);
    myInit();

    // enable 3D
    glEnable(GL_DEPTH_TEST);
    // attach spinning to idle func
    glutIdleFunc(spinCube);
    // attach mouse function to change axis
    glutMouseFunc(mouse);
    // ensure window reshaping doesnt affect drawing
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}