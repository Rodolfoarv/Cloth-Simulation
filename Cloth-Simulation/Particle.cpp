#include "Particle.h"


Particle::Particle()
#define DAMPING 0.01 // how much to damp the cloth simulation each frame
#define TIME_STEPSIZE2 0.5*0.5 // how large time step each particle takes each frame

{
}


Particle::~Particle()
{
}

Particle::Particle(Vec3 pos) : pos(pos), old_pos(pos), acceleration(Vec3(0, 0, 0)), mass(1), movable(true), accumulated_normal(Vec3(0, 0, 0)){}

void Particle::timeStep()
{
	if (movable)
	{
		Vec3 temp = pos;
		pos = pos + (pos - old_pos)*(1.0 - DAMPING) + acceleration*TIME_STEPSIZE2;
		old_pos = temp;
		acceleration = Vec3(0, 0, 0); // acceleration is reset since it HAS been translated into a change in position (and implicitely into velocity)	
	}
}

Vec3& Particle::getPos() { return pos; }

void Particle::resetAcceleration() { acceleration = Vec3(0, 0, 0); }

void Particle::offsetPos(const Vec3 v) { if (movable) pos += v; }

void Particle::makeUnmovable() { movable = false; }

void Particle::addToNormal(Vec3 normal)
{
	accumulated_normal += normal.normalized();
}

Vec3& Particle::getNormal() { return accumulated_normal; } // notice, the normal is not unit length

void Particle::resetNormal() { accumulated_normal = Vec3(0, 0, 0); }