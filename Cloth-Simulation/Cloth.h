#pragma once
#include <vector>
#include "Particle.h"
#include "Constraint.h"
#include <GL/gl.h>
#include <GL/glut.h> 
class Cloth
{
private:
	int num_particles_width; // number of particles in "width" direction
	int num_particles_height; // number of particles in "height" direction
	std::vector<Particle> particles;
	std::vector<Constraint> constraints;
	void makeConstraint(Particle *p1, Particle *p2);
	Particle* getParticle(int x, int y);
	Vec3 calcTriangleNormal(Particle *p1, Particle *p2, Particle *p3);
	void drawTriangle(Particle *p1, Particle *p2, Particle *p3, const Vec3 color);

public:
	Cloth();
	~Cloth();
	Cloth(float width, float height, int num_particles_width, int num_particles_height);
	void addForce(const Vec3 direction);
	void drawShaded();
	
};



