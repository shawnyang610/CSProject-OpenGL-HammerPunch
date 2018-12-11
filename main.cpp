#include <iostream>
// for Linux
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glut.h>

// for OSX
//#include <GLUT/glut.h>


// EXAMPLE P.168

GLfloat pos[] = {-2, 4, 5, 1}, amb[] = {0.3, 0.3, 0.3, 1.0};
GLfloat front_amb_diff[] = {0.7, 0.5, 0.1, 1.0};
GLfloat back_amb_diff[] = {0.4, 0.7, 0.1, 1.0};
GLfloat spe[] = {0.25, 0.25, 0.25, 1.0};
GLfloat theta = 0, dt = 0.5, axes[3][3] = {{1, 0, 0},
                                           {0, 1, 0},
                                           {0, 0, 1}};
int axis = 0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    if (axis < 3) {
        glRotated(theta, axes[axis][0], axes[axis][1], axes[axis][2]);
    } else {
        glPushMatrix();
        glRotated(theta, 0, 0, 1);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        glPopMatrix();
    }
//    glutSolidTeapot(1);
//    glutSolidTorus(0.1,0.5, 48, 96);
//    glutSolidCone(1,1,48,24);
//    glutSolidDodecahedron();
//    glutWireIcosahedron();
//    GLUquadricObj *p=gluNewQuadric();
//    gluCylinder(p, 0, 5, 15,100, 50);
    gluCylinder(gluNewQuadric(), 0.2, 0.2, 1, 4, 10);
    glPopMatrix();
    glutSwapBuffers();
}

void idle(void) {
    if (theta >= 360) axis = (axis + 1) % 4;
    theta = (theta < 360) ? theta + dt : dt;
    glutPostRedisplay();
}


//void mouse(int button, int state, int x, int y) {
//    if (button == GLUT_LEFT_BUTTON) {
//        if (state == GLUT_DOWN) {
//            v = n++;
//            vert[v][0] = x;
//            vert[v][1] = height - 1 - y;
//
//            glutPostRedisplay();
//        }
//    }
//}
//
//    void motion(int x, int y) {
//        if (rubberbanding) {
//            vert[v][0] = x;
//            vert[v][1] = height - y - 1;
//            glutPostRedisplay();
//        }
//    }

    int main(int argc, char **argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 800);
        glutInitWindowPosition(200, 100);
        glutCreateWindow("Shawn's Final Project");
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glEnable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();
        gluPerspective(45, 1.0, 2, 8);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
        glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(0, 0, -5);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutMainLoop();

    }

// END OF EXAMPLE P.168