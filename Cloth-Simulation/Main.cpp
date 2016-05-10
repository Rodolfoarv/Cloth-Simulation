#include "Main.h"
#include <GL/glut.h> 
#include <GL/gl.h>
#include "Cloth.h"
#include "Vec3.h"

#define TIME_STEPSIZE2 0.5*0.5 // how large time step each particle takes each frame

Cloth cloth1(14, 10, 55, 45); 
Vec3 ball_pos(7, -5, 0); // the center of our one ball
float ball_radius = 2; // the radius of our one ball
float ballPos_z = 0; // counter for used to calculate the z position of the ball below
float ballPos_x = 0; // counter for used to calculate the x position of the ball below


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
	glDisable(GL_LIGHTING); 
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-200.0f, -100.0f, -100.0f);
	glVertex3f(200.0f, -100.0f, -100.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(200.0f, 100.0f, -100.0f);
	glVertex3f(-200.0f, 100.0f, -100.0f);
	glEnd();
	glEnable(GL_LIGHTING);

	glTranslatef(-6.5, 6, -9.0f); 
	glRotatef(12, 0, 1, 0); 
	cloth1.drawShaded(); 

	//BALL
	//glPushMatrix(); // to draw the ball we use glutSolidSphere, and need to draw the sphere at the position of the ball
	glTranslatef(ball_pos.f[0], ball_pos.f[1], ball_pos.f[2]); // hence the translation of the sphere onto the ball position
	glColor3f(1, 1, 1);
	glutSolidSphere(ball_radius , 50, 50); // draw the ball, but with a slightly lower radius, otherwise we could get ugly visual artifacts of cloth penetrating the ball slightly
	//glPopMatrix();


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
	case 97:
		//A
		ballPos_x--;
		ball_pos.f[0] = cos(ballPos_x / 50.0) * 7;
		break;
	case 100:
		//D
		ballPos_x++;
		ball_pos.f[0] = cos(ballPos_x / 50.0) * 7;
		break;
	case 119:
		//W
		ballPos_z++;
		ball_pos.f[2] = cos(ballPos_z / 50.0) * 7;
		break;
	case 115:
		//S
		ballPos_z--;
		ball_pos.f[2] = cos(ballPos_z / 50.0) * 7;
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



