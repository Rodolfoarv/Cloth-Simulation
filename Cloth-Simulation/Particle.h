#pragma once
#include "Vec3.h"
class Particle
{
private: 
	bool movable; // Boolean variable that is used to determine if the particle should move or not

	float mass;
	Vec3 pos;
	Vec3 old_pos;
	Vec3 acceleration;
	Vec3 accumulated_normal;

public:
	Particle();
	~Particle();
	Particle(Vec3 pos);
	void addForce(Vec3 f);
	void timeStep();
	Vec3& getPos();
	void resetAcceleration();
	void offsetPos(const Vec3 v);
	void makeUnmovable();
	void addToNormal(Vec3 normal);
	Vec3& getNormal();
	void resetNormal();

};

