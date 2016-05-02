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
	// making the upper left most three and right most three particles unmovable
	for (int i = 0; i<3; i++)
	{
		getParticle(0 + i, 0)->offsetPos(Vec3(0.5, 0.0, 0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
		getParticle(0 + i, 0)->makeUnmovable();

		getParticle(0 + i, 0)->offsetPos(Vec3(-0.5, 0.0, 0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
		getParticle(num_particles_width - 1 - i, 0)->makeUnmovable();
	}

}


