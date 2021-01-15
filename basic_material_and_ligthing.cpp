/**
 * Use ligting example.
 * Place a light point.
 * Draw 2 rectangles in perspective (based on vertex and normal data).
 * Show how 2 faces are lit differently (depending on the angle).
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <iostream>

GLfloat polygonData[] = {
    -2.0, 0.0, 0.0,
    2.0, 0.0, 0.0,
    2.0, 0.0, 3.0,
    -2.0, 0.0, 3.0,

    2.0, 0.0, 0.0,
    5.0, 3.0, 0.0,
    5.0, 3.0, 3.0,
    2.0, 0.0, 3.0
};

GLfloat polygonNormalData[] = {
    0.0,-1.0,0.0,
    0.0,-1.0,0.0,
    0.0,-1.0,0.0,
    0.0,-1.0,0.0,

    0.5,-0.5,0.0,
    0.5,-0.5,0.0,
    0.5,-0.5,0.0,
    0.5,-0.5,0.0,
};

GLfloat materialDiffuse[] = {
    1.0, 1.0, 0.0, 1.0
};

GLfloat lightSpecular[] = {
    1.0, 1.0, 1.0, 1.0
};

GLfloat lightPosition[] = {
   1.0, -15.0, 5.0, 0.0
};

void draw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // enter modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,-15.0,3.0, 0.0,0.0,0.0, 0.0,0.0,1.0);

    // set light color and  position
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // draw polygon
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, polygonData);
    glNormalPointer(GL_FLOAT, 0, polygonNormalData);
    glBegin(GL_QUADS);
    for (int i = 0; i < 8; i++)
    {
        glArrayElement(i);
    }
    glEnd();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    // draw a sphere for reference
    glutSolidSphere (1.0, 20, 16);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // setup perspective : angle, aspect ratio (width and height),
    // near plane and far plane distance from camera
    gluPerspective(45.0, 1.0, 9.0, 35.0);
    glMatrixMode(GL_MODELVIEW);
}

void idleFunction()
{
    lightPosition[2] += 0.4;
    glutPostRedisplay();
    usleep(20000);
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Test");
 
    init();
   
    glutDisplayFunc(draw);
    glutIdleFunc(idleFunction);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
