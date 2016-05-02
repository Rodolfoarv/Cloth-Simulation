#pragma once
#include <vector>
#include "Particle.h"
#include "Constraint.h"
class Cloth
{
private:
	int num_particles_width; // number of particles in "width" direction
	int num_particles_height; // number of particles in "height" direction
	std::vector<Particle> particles;
	std::vector<Constraint> constraints;



public:
	Cloth();
	~Cloth();
	Cloth(float width, float height, int num_particles_width, int num_particles_height);
	void addForce(const Vec3 direction);
	Particle* getParticle(int x, int y);
};



