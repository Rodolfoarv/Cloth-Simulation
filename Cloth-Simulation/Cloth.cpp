#include "Cloth.h"


Cloth::Cloth()
{
}


Cloth::~Cloth()
{
}

Particle* Cloth::getParticle(int x, int y) { return &particles[y*num_particles_width + x]; }


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

	// making the upper left most three and right most three particles unmovable
	for (int i = 0; i<3; i++)
	{
		//In order to make the particle to hang more on the center
		getParticle(0 + i, 0)->offsetPos(Vec3(0.5, 0.0, 0.0)); 
		getParticle(0 + i, 0)->makeUnmovable();
		getParticle(0 + i, 0)->offsetPos(Vec3(-0.5, 0.0, 0.0)); 
		getParticle(num_particles_width - 1 - i, 0)->makeUnmovable();
	}

}


