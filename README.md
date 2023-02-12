# CGVR-lab-programs

## List of programs for CGVR lab (7th sem)
1) Bresenham Line
2) Bresenham Circle
3) Double buffer (spin rectangle)
4) Cylinder and Parallellopiped
5) 3D Sierpinski gasket
6) 3D sphere approximation
7) Scan-line filling algorithm
8) Cohen Sutherland line clipping
9) Liang-Barsky line clipping
10) Cohen-hedgeman polygon clipping
11) House rotation and reflection
12) Color cube and spinning it

## How to run these programs
I followed this tutorial (https://medium.com/swlh/setting-opengl-for-windows-d0b45062caf)

And instead of running on codeblocks, programs are compiled directly with this command

```
gcc prog.c -I"C:\msys64\mingw64\include" -lopengl32 -lglu32 -lfreeglut
```

## General openGL workings
Some general info to be kept in mind

### For 2D stuff camera setup
```gluOrtho2D(int left, int right, int bottom, int top)```

### For 3D stuff camera setup
```glOrtho(int left, int right, int bottom, int top, int near, int far)```

### Never forget to call glFlush()
It is responsinle for pushing whatever is in display buffer onto screen. If not called, rendering might not be seen.
Generally, call this whenever anything is drawn or updated onto screen.

### Use glEnable(GL_DEPTH_TEST)
When any 3D stuff is happening or some so rt of animation, use this always.
In addition to this, add GLUT_DEPTH to glutInitDisplay() and GL_DEPTH_BUFFER_BIT to glClear().

### For animations
Never forget ```glFlush()```. Some programs might need ```glutPostRedisplay()```, remember this also.

### Geometric Transformations
Use glRotatef / glTranslatef / glScalef. These apply transformations on whole scene.
To apply to just one drawing, use this method -

```
glPushMatrix();
glRotatef(...) or whatever trasformations

... draw stuff ...

glPopMatrix();
```

### Rotation about fixed point
About fixed point, you need to carry out Translation, then Rotation, then inverse Translation
```
glTranslatef(x,y,0);
glRotatef(angle, x,y,z);
glTranslatef(-x,-y,0);
```

### Reflection about a line
We do Translaton, Rotation, Scale, inverse Rotate, inverse Translate
```
glTranslatef(0,c,0);  // c is the y-intercept
glRotatef(angle, 0, 0, 1);  // angle = atan(slope) * RADIAN2DEGREE
glScalef(1,-1,1);
glRotatef(angle, 0, 0, 1);
glTranslatef(0,-c,0);
```

### Having more than one window
Keep reference of window_id of each window, and possibly assign different display() functions.
Within display(), call ```glutSetWindow(window_id)``` first.

### For 3D sphere approximation
To view the sphere properly, use these functions
```
// this makes sure only lines are colored and polygons are not filled
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

// removal of back faces so sphere can be viewed easily
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK); 
```

### For drawing lines with mouse
In case camera is set using ```gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2)```, use this to draw line

```drawLine(xglobal-WIDTH/2, HEIGHT/2-yglobal, x-WIDTH/2, HEIGHT/2-y);```

In case camera is set using  ```gluOrtho2D(0, WIDTH, 0, HEIGHT)```, use this to draw line

```drawLine(xglobal, HEIGHT-yglobal, x, HEIGHT-y);```

### Edit 1: RV folks who are forced to use Visual Studio 2010
Function calls to math functions like sqrt and sin,cos,tan may throw errors

To fix this, do typecasting of the function arguments to float or double

Example: instead of doing ```sqrt(x)```, use ```sqrt((float)x)```
