#include "Main.h"
#include <GL/glut.h> 
#include <GL/gl.h>
#include "Cloth.h"
#include "Vec3.h"

#define TIME_STEPSIZE2 0.5*0.5 // how large time step each particle takes each frame

Cloth cloth1(14, 10, 55, 45); 

void init(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.2f, 0.2f, 0.4f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightPos[4] = { -1.0, 1.0, 0.5, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat *)&lightPos);

	glEnable(GL_LIGHT1);

	GLfloat lightAmbient1[4] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat lightPos1[4] = { 1.0, 0.0, -0.2, 0.0 };
	GLfloat lightDiffuse1[4] = { 0.5, 0.5, 0.3, 0.0 };

	glLightfv(GL_LIGHT1, GL_POSITION, (GLfloat *)&lightPos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, (GLfloat *)&lightAmbient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat *)&lightDiffuse1);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void draw(void){
	// drawing

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glDisable(GL_LIGHTING); // drawing some smooth shaded background - because I like it ;)
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-200.0f, -100.0f, -100.0f);
	glVertex3f(200.0f, -100.0f, -100.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(200.0f, 100.0f, -100.0f);
	glVertex3f(-200.0f, 100.0f, -100.0f);
	glEnd();
	glEnable(GL_LIGHTING);

	glTranslatef(-6.5, 6, -9.0f); // move camera out and center on the cloth
	glRotatef(12, 0, 1, 0); // rotate a bit to see the cloth from the side
	cloth1.drawShaded(); // finally draw the cloth with smooth shading

	glutSwapBuffers();
	glutPostRedisplay();
}

void displayForces(void){
	cloth1.addForce(Vec3(0, -0.2, 0)*TIME_STEPSIZE2); // GRAVITY FORCE
	cloth1.windForce(Vec3(1.5, 0, 0.2)*TIME_STEPSIZE2); // WIND FORCE EACH FRAME
	cloth1.timeStep(); // calculate the particle positions of the next frame
}
/* display method called each frame*/
void display(void)
{
	// calculating positions
	displayForces();
	draw();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h == 0)
		gluPerspective(80, (float)w, 1.0, 5000.0);
	else
		gluPerspective(80, (float)w / (float)h, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);

	glutCreateWindow("Cloth Simulation");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);


	glutMainLoop();
}



