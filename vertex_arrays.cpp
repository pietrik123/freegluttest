/*
 * Draw a red square [(1,1,0),(-1,1,0),(-1,-1,0),(1,-1,0)] and
 * a green triangle [(4,1,0),(3,3,0),(2,1,0)].
 * Place a camera at (0,0,10) and make it look at (0,0,0), oriented along
 * global Y axis (0,1,0).
 * Make the camera move away from drawn shapes (each program cycle).
 *
 * Do the following transforms: translate square with vector [-1,0,0] 
 * - one time action.
 * Make it rotate around local Y axis (animated).
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>

static float distanceDelta = 0.0;
static float angle = 0.0;

GLfloat squareData[][3] = {
    {1.0, 1.0, 0.0},
    {-1.0, 1.0, 0.0},
    {-1.0,-1.0, 0.0},
    {1.0, -1.0, 0.0}
};

GLfloat triangleData[] = {
    4.0, 1.0, 0.0,
    3.0, 3.0, 0.0,
    2.0, 1.0, 0.0
};

void draw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    // enter modelview
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(0.0,0.0,10.0+distanceDelta, 0.0,0.0,0.0, 0.0, 1.0, 0.0);

    // draw square
    glPushMatrix();
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef(45.0 + angle, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < 4; i++)
    {
        glVertex3fv(squareData[i]);
    }
    glEnd();
    glPopMatrix();

    // draw triangle
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, triangleData);
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i < 3; i++)
    {
        glArrayElement(i);
    }
    glEnd();  
    glDisableClientState(GL_VERTEX_ARRAY);

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
    distanceDelta += 0.05;
    angle += 2.0;
    glutPostRedisplay();
    usleep(20000);
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
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
