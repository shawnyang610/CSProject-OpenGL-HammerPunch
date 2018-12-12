#include <iostream>
#include <cmath>
// for Linux
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glut.h>

// for OSX
//#include <GLUT/glut.h>


// EXAMPLE P.168

GLfloat pos[] = {-1, 5, 2, 1}, amb[] = {0.1, 0.1, 0.1, 0.5};
GLfloat HAMMERHEAD_FRONT_AMB_DIFU[] = {1, 0.3, 0.3, 0.2};
GLfloat HANDLE_FRONT_AMB_DIFU[] = {1,0.8,0.2,0.2};
GLfloat UPPER_HANDLE_FRONT_AMB_DIFU[] = {0.6,0.6,0.6,0.6};
GLfloat LOWER_HANDLE_FRONT_AMB_DIFU[] = {1,0.6,0.1,0.2};
int idle_sign =1;
GLfloat back_amb_diff[] = {0.4, 0.7, 0.1, 1.0};
GLfloat spe[] = {0.25, 0.25, 0.25, 1.0};
bool swing =true, demo=true;
GLfloat position_offset[3] ={0,0,0};
//GLfloat theta = 0, dt = 0.5, axes[3][3] = {{1, 0, 0},
//                                           {0, 1, 0},
//                                           {0, 0, 1}};
//int axis = 0;
//
//void display(void) {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glPushMatrix();
//    if (axis < 3) {
//        glRotated(theta, axes[axis][0], axes[axis][1], axes[axis][2]);
//    } else {
//        glPushMatrix();
//        glRotated(theta, 0, 0, 1);
//        glLightfv(GL_LIGHT0, GL_POSITION, pos);
//        glPopMatrix();
//    }
////    glutSolidTeapot(1);
////    glutSolidTorus(0.1,0.5, 48, 96);
////    glutSolidCone(1,1,48,24);
////    glutSolidDodecahedron();
////    glutWireIcosahedron();
////    GLUquadricObj *p=gluNewQuadric();
////    gluCylinder(p, 0, 5, 15,100, 50);
//    gluCylinder(gluNewQuadric(), 0.2, 0.2, 1, 4, 10);
//    glPopMatrix();
//    glutSwapBuffers();
//}
//





int WIDTH = 800, HEIGHT = 800;
GLint ref_point[3] = {0, 0, 0};
GLint theta[3] = {0, 0, 0};
GLint theta_idle[3] = {0,0,0};
GLdouble HAMMERHEAD_LENGTH = 2.0;
GLdouble HANDLE_TOP = 0.1, HANDLE_BASE = 0.2, HANDLE_LENGTH = 2.8;
GLdouble CONE_BASE = 0.6, CONE_HEIGHT = 0.2;
GLdouble HAMMERHEAD_SHAFT_BASE = 0.4, HAMMERHEAD_SHAFT_TOP = 0.4, HAMMERHEAD_SHAFT_LENGTH = 0.25;


void idle(void) {
    if (demo && theta[2]==0) swing= true;
    if (swing) {
        theta[2] = 5;
        idle_sign=1;
    }
    if (theta[2]>0){
//        if (theta[2] == 0) idle_sign = 1;
        if (theta[2] == 90) idle_sign = -1;
        if (swing ==false || idle_sign==-1)
            theta[2] = theta[2] + 5 * idle_sign;
        swing = false;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {

//            ref_point[0] = x;
//            ref_point[1] = HEIGHT - 1 - y;

//            glutPostRedisplay();
        }
        else swing = true;
        demo =false;
    }
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 'r':
            demo = true;
            swing =true;
            theta[0] = 0;
            theta[1] =0;
            theta[2] =0;
            position_offset[0]=0;
            position_offset[1]=0;
            position_offset[2]=0;

            break;

        case 'a':
            position_offset[0]-=0.1;
            break;
        case 'd':
            position_offset[0]+=0.1;
            break;
        case 's':
            position_offset[1]-=0.1;
            break;
        case 'w':
            position_offset[1]+=0.1;
            break;
    }
    glutPostRedisplay();
}


void motion(int x, int y) {
    theta[0] = x;
    theta[1] = HEIGHT - y - 1;
    glutPostRedisplay();
}

void rectangle(float position[4][3]){
    glPushMatrix();
//    glColor3f(0.15, 0.39, 0.77);
    glBegin(GL_POLYGON);
    for (int i=0; i<4; i++){
        glVertex3fv(position[i]);
    }
    glEnd();
    glPopMatrix();
}

void circle() {
    glPushMatrix();
    glutSolidCone(CONE_BASE, 0.06, 20, 10);
    glPopMatrix();
}

void single_cone() {
    glPushMatrix();
    glutSolidCone(CONE_BASE, CONE_HEIGHT, 15, 20);
    glPopMatrix();
}

void double_cone_cover(){
    glPushMatrix();
    single_cone();
    glRotated(180, 0, 1, 0);
    circle();
    glPopMatrix();
}

void double_cone() {
    glPushMatrix();
    single_cone();
    glRotated(180, 0, 1, 0);
    single_cone();
    glPopMatrix();
}

void uppper_handle(){
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, HAMMERHEAD_FRONT_AMB_DIFU);
    float multipier =0.9;
    float handle_cap[4][3] = {{(GLfloat)-HANDLE_BASE*multipier,(GLfloat)HANDLE_BASE*multipier,0},
                                 {(GLfloat)HANDLE_BASE*multipier,(GLfloat)HANDLE_BASE*multipier,0},
                                 {(GLfloat)HANDLE_BASE*multipier,(GLfloat)-HANDLE_BASE*multipier,0},
                                 {(GLfloat)-HANDLE_BASE*multipier,(GLfloat)-HANDLE_BASE*multipier,0}};
    glPushMatrix();
    gluCylinder(gluNewQuadric(), HANDLE_BASE*1.2, HANDLE_BASE, HANDLE_LENGTH/50.0, 4, 20);
    glPushMatrix();
//    glTranslated(0,0,-0.01);
    glRotated(45,0,0,1);
    rectangle(handle_cap);
    glPopMatrix();
    glPopMatrix();
}
void lower_handle() {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, LOWER_HANDLE_FRONT_AMB_DIFU);
    float multipier =0.72;
    float handle_cap[4][3] = {{(GLfloat)-HANDLE_TOP*multipier,(GLfloat)HANDLE_TOP*multipier,0},
                              {(GLfloat)HANDLE_TOP*multipier,(GLfloat)HANDLE_TOP*multipier,0},
                              {(GLfloat)HANDLE_TOP*multipier,(GLfloat)-HANDLE_TOP*multipier,0},
                              {(GLfloat)-HANDLE_TOP*multipier,(GLfloat)-HANDLE_TOP*multipier,0}};

//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, HAMMERHEAD_FRONT_AMB_DIFU);

    glPushMatrix();
    gluCylinder(gluNewQuadric(), (HANDLE_BASE-HANDLE_TOP)*0.26+HANDLE_TOP, HANDLE_TOP, HANDLE_LENGTH/4.0, 4, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,HANDLE_LENGTH/4.0);
    glRotated(45,0,0,1);
    glRotated(180,0,1,0);
    rectangle(handle_cap);
    glPopMatrix();
}

void draw_handle() {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, HANDLE_FRONT_AMB_DIFU);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);

    glPushMatrix();
    glTranslated(0, 0, -0.2);
    glRotated(45, 0, 0, 1);
    gluCylinder(gluNewQuadric(), HANDLE_BASE, HANDLE_TOP, HANDLE_LENGTH, 4, 60);

    glPushMatrix();
    glTranslated(0,0,HANDLE_LENGTH/4.0*3);
    lower_handle();
    glPopMatrix();

    uppper_handle();

    glPopMatrix();

}



void draw_hammerhead_center() {
    glPushMatrix();
        glTranslated(-HAMMERHEAD_SHAFT_LENGTH/2.0, 0, 0.5);
        glRotated(90, 0, 1, 0);
        gluCylinder(gluNewQuadric(), HAMMERHEAD_SHAFT_BASE, HAMMERHEAD_SHAFT_TOP, HAMMERHEAD_SHAFT_LENGTH, 20, 10);
    glPopMatrix();
}

void draw_hammerhead_ring(void (*cone_functions)(void)) {
    glPushMatrix();
    // align and wrap around the hammerhead_center
    glTranslated(0, 0, 0.5);
    glRotated(90, 0, 1, 0);
    cone_functions();
    glPopMatrix();
}

void draw_hammerhead_rings_both_sides() {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, HAMMERHEAD_FRONT_AMB_DIFU);
//    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, HAMMERHEAD_FRONT_AMB_DIFU);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
//    glDisable(GL_COLOR);
    glPushMatrix();
       // move rings off the handle part
        GLdouble off_center = HANDLE_BASE * 0.9;
        GLdouble hammerhead_length_each_side = (HAMMERHEAD_LENGTH - off_center * 2) / 2;
        glPushMatrix();
            glTranslated(-off_center, 0, 0);
            int num_of_rings_each_side = hammerhead_length_each_side / (CONE_HEIGHT * 0.6);

                for (int i = 0; i < num_of_rings_each_side; i++) {
                    glPushMatrix();
                    glTranslated(-i * CONE_HEIGHT * 0.7, 0, 0);

                    if (i < num_of_rings_each_side - 1) {
                        draw_hammerhead_ring(double_cone);
                    }
                    else {
                        draw_hammerhead_ring(double_cone_cover);
                    }
                    glPopMatrix();
                }
        glPopMatrix();
        glPushMatrix();
        glTranslated(off_center, 0, 0);
        for (int i = 0; i < num_of_rings_each_side; i++) {
            glPushMatrix();
            glTranslated(i * CONE_HEIGHT * 0.7, 0, 0);

            if (i < num_of_rings_each_side - 1) {
                draw_hammerhead_ring(double_cone);
            }
            else {
                glRotated(180, 0,0,1);
                draw_hammerhead_ring(double_cone_cover);
            }
            glPopMatrix();
        }
        glPopMatrix();

        draw_hammerhead_center();

    glPopMatrix();
}


void draw_hammer(){
    glPushMatrix();
    glTranslated(0,2.2,0);
    glRotated(90,1,0,0);
    draw_handle();
    draw_hammerhead_rings_both_sides();
    glPopMatrix();
}

void text(char* text, float x, float y, float z){
    glPushMatrix();
        glTranslated(x, y,z);
        glColor3f(1,1,0);
        glLineWidth(3.0);
        glRasterPos3f(-2,0,0);
        for (char* c=text; *c !=NULL ;c++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    text("Toy Hammer",1.5,2.5,0);
    text("Click mouse to stop and move the hammer",1,2.2,0);


    glPushMatrix();
        glTranslated(0+position_offset[0],-1+position_offset[1],-1+position_offset[2]);
        glRotated(theta[0] - ref_point[0], 0, 1, 0);
        glRotated(theta[1] - ref_point[1], 1, 0, 0);
        glRotated(theta[2] - ref_point[2], 0, 0, 1);

        draw_hammer();

    glPopMatrix();

    glutSwapBuffers();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Shawn's Final Project");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45, 1.0, 1, 20);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
//    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
//    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0, 0, -7);
//    glRotated(90, 0, 0, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();

}

// END OF EXAMPLE P.168