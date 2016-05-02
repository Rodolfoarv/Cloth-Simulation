#pragma once
#include "Particle.h"
class Constraint
{
private:
	float rest_distance; // the length between particle p1 and p2 in rest configuration
public:
	Constraint();
	~Constraint();

	Particle *p1, *p2;
	Constraint(Particle *p1, Particle *p2);
	void satisfyConstraint();

};

