/*
 * Texture example. Program uses bitmap loader:
 * https://github.com/ArashPartow/bitmap
 *
 * Loads texture from file. Applies texture to a triangle.
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <unistd.h>

#include "bitmap_image.hpp"


static bitmap_image* image;
static GLubyte* texData;
static GLuint texName;

static GLfloat triangleData[] = {
    2.0, 0.0, 0.0,
    0.0, 4.5, 0.0,
    -2.0, 0.0, 0.0
};

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 9.0, 35.0);
    glMatrixMode(GL_MODELVIEW);
}

void idleFunction()
{
    glutPostRedisplay();
    usleep(20000);
}

void displayFunction()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,10.0,
              0.0,0.0,0.0,
              0.0,1.0,0.0);

    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, triangleData);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0, 0.0);
    glArrayElement(2);
    glTexCoord2f(0.5, 1.0);
    glArrayElement(1);
    glTexCoord2f(1.0,0.0);
    glArrayElement(0);
    glEnd();
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();

    glutSwapBuffers();
}

void keyboardFunction(unsigned char key, int x, int y)
{
}

int init(char* filename)
{
    glClearColor(0.2,0.2,0.2,1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
     
    image = new bitmap_image(filename);
    if (!image)
    {   
        std::cout << "Error in loading texture!\n";
        return -1;
    }

    image->vertical_flip();
    image->reverse_channels();
    texData = image->data();

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width(), image->height(),
            0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
    glEnable(GL_TEXTURE_2D);
}

void cleanup()
{
    delete image;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(400,400);
    glutInitWindowPosition(100,100);
    glutCreateWindow("test");

    if (argc < 2)
    {
        std::cout << "Please specify filename!\n";
        return -1;
    }
    if (init(argv[1]) == -1) return -1;

    glutDisplayFunc(displayFunction);
    glutKeyboardFunc(keyboardFunction);
    glutIdleFunc(idleFunction);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
