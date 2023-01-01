/*
Write a program to demonstrate the approximation of a 3D sphere with appropriate mathematical formulations. Write the complete C program to approximate a sphere using OpenGL primitives.
*/

#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

#define WIDTH  500
#define HEIGHT 500
#define D2R (3.14/180.0)    // degree to radian conversion factor
#define RADIUS 200

struct point {
    int x,y,z;
};

struct point calcPoint(int theta, int phi)
{
    struct point p1;
    p1.x = RADIUS * sin(theta * D2R) * cos(phi * D2R);
    p1.y = RADIUS * cos(theta * D2R) * cos(phi * D2R);
    p1.z = RADIUS * sin(phi * D2R);
    return p1;
}

void display()
{
    glPushMatrix();
    glRotatef(20,0,1,0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // this function shows just the lines, make sure you include it
    glColor3f(0,0,1);

    // draw the body
    for(int phi=-80; phi<=80; phi+=10)
    {
        glBegin(GL_QUAD_STRIP);
        for(int theta=-180; theta<=180; theta+=10)
        {
            struct point p1, p2;

            p1 = calcPoint(theta, phi);
            glVertex3f(p1.x, p1.y, p1.z);

            p2 = calcPoint(theta, phi+10);
            glVertex3f(p2.x, p2.y, p2.z);
        }
        glEnd();
    }
    
    // draw north cap
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,RADIUS);
    for(int theta=-180; theta<=180; theta+=10)
    {
        struct point p = calcPoint(theta, 80);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
    
    // draw south cap
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,-RADIUS);
    for(int theta=-180; theta<=180; theta+=10)
    {
        struct point p = calcPoint(theta, -80);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    glPopMatrix();

    glFlush();
}

void myInit()
{
    // set background color
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set camera (3D space)
    glOrtho(-250,250,-250,250,-250,250);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D Sphere Approximation");
    myInit();
    glutDisplayFunc(display);

    // this is optional, but it removes back faces so sphere can be viewed nicely
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //glEnable(GL_DEPTH_TEST);  // try de-commenting if code doesn't work

    glutMainLoop();
    return 0;
}