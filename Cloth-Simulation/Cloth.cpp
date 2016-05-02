#include "Cloth.h"
#include <math.h>
#include <GL/glut.h> 
#include <GL/gl.h>

#define CONSTRAINT_ITERATIONS 15 // How rigid and how soft the cloth will be 



Cloth::Cloth()
{
}


Cloth::~Cloth()
{
}

Particle* Cloth::getParticle(int x, int y) { return &particles[y*num_particles_width + x]; }
void Cloth::makeConstraint(Particle *p1, Particle *p2) { constraints.push_back(Constraint(p1, p2)); }

Vec3 calcTriangleNormal(Particle *p1, Particle *p2, Particle *p3)
{
	Vec3 pos1 = p1->getPos();
	Vec3 pos2 = p2->getPos();
	Vec3 pos3 = p3->getPos();

	Vec3 v1 = pos2 - pos1;
	Vec3 v2 = pos3 - pos1;

	return v1.cross(v2);
}

void drawTriangle(Particle *p1, Particle *p2, Particle *p3, const Vec3 color)
{
	glColor3fv((GLfloat*)&color);

	glNormal3fv((GLfloat *)&(p1->getNormal().normalized()));
	glVertex3fv((GLfloat *)&(p1->getPos()));

	glNormal3fv((GLfloat *)&(p2->getNormal().normalized()));
	glVertex3fv((GLfloat *)&(p2->getPos()));

	glNormal3fv((GLfloat *)&(p3->getNormal().normalized()));
	glVertex3fv((GLfloat *)&(p3->getPos()));
}

Cloth::Cloth(float width, float height, int num_particles_width, int num_particles_height)
	: num_particles_width(num_particles_width), num_particles_height(num_particles_height)
{
	particles.resize(num_particles_width*num_particles_height); 

	// Creates the particle from 0,0,0 to the width and height being specified
	for (int x = 0; x<num_particles_width; x++)
	{
		for (int y = 0; y<num_particles_height; y++)
		{
			Vec3 pos = Vec3(width * (x / (float)num_particles_width),
				-height * (y / (float)num_particles_height),
				0);
			particles[y*num_particles_width + x] = Particle(pos); // insert particle in column x at y'th row
		}
	}

	// Connecting the immediate neighbor particles with the constraints
	for (int x = 0; x<num_particles_width; x++)
	{
		for (int y = 0; y<num_particles_height; y++)
		{
			if (x<num_particles_width - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y));
			if (y<num_particles_height - 1) makeConstraint(getParticle(x, y), getParticle(x, y + 1));
			if (x<num_particles_width - 1 && y<num_particles_height - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y + 1));
			if (x<num_particles_width - 1 && y<num_particles_height - 1) makeConstraint(getParticle(x + 1, y), getParticle(x, y + 1));
		}
	}

	// Connecting secondary neighbors with the constraints
	for (int x = 0; x<num_particles_width; x++)
	{
		for (int y = 0; y<num_particles_height; y++)
		{
			if (x<num_particles_width - 2) makeConstraint(getParticle(x, y), getParticle(x + 2, y));
			if (y<num_particles_height - 2) makeConstraint(getParticle(x, y), getParticle(x, y + 2));
			if (x<num_particles_width - 2 && y<num_particles_height - 2) makeConstraint(getParticle(x, y), getParticle(x + 2, y + 2));
			if (x<num_particles_width - 2 && y<num_particles_height - 2) makeConstraint(getParticle(x + 2, y), getParticle(x, y + 2));
		}
	}



	// These will be the pins
	for (int i = 0; i<3; i++)
	{
		//In order to make the particle to hang more on the center
		getParticle(0 + i, 0)->offsetPos(Vec3(0.5, 0.0, 0.0)); 
		getParticle(0 + i, 0)->makeUnmovable();
		getParticle(0 + i, 0)->offsetPos(Vec3(-0.5, 0.0, 0.0)); 
		getParticle(num_particles_width - 1 - i, 0)->makeUnmovable();
	}

}

void Cloth::drawShaded(){

	//Reset the normals
	std::vector<Particle>::iterator particle;
	for (particle = particles.begin(); particle != particles.end(); particle++)
	{
		(*particle).resetNormal();
	}

	for (int x = 0; x<num_particles_width - 1; x++)
	{
		for (int y = 0; y<num_particles_height - 1; y++)
		{
			Vec3 normal = calcTriangleNormal(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1));
			getParticle(x + 1, y)->addToNormal(normal);
			getParticle(x, y)->addToNormal(normal);
			getParticle(x, y + 1)->addToNormal(normal);

			normal = calcTriangleNormal(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1));
			getParticle(x + 1, y + 1)->addToNormal(normal);
			getParticle(x + 1, y)->addToNormal(normal);
			getParticle(x, y + 1)->addToNormal(normal);
		}
	}
	glBegin(GL_TRIANGLES);
	for (int x = 0; x<num_particles_width - 1; x++)
	{
		for (int y = 0; y<num_particles_height - 1; y++)
		{
			Vec3 color(0, 0, 0);
			if (x % 2) // red and white color is interleaved according to which column number
				color = Vec3(0.6f, 0.2f, 0.2f);
			else
				color = Vec3(1.0f, 1.0f, 1.0f);

			drawTriangle(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1), color);
			drawTriangle(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1), color);
		}
	}

	glEnd();
}

void Cloth::timeStep()
{
	std::vector<Constraint>::iterator constraint;
	for (int i = 0; i<CONSTRAINT_ITERATIONS; i++) // iterate over all constraints several times
	{
		for (constraint = constraints.begin(); constraint != constraints.end(); constraint++)
		{
			(*constraint).satisfyConstraint(); // satisfy constraint.
		}
	}

	std::vector<Particle>::iterator particle;
	for (particle = particles.begin(); particle != particles.end(); particle++)
	{
		(*particle).timeStep(); // calculate the position of each particle at the next time step.
	}
}

