//lib includes
#include <glut.h> 
#include <math.h>
#include <vector>
#include <iostream>
#include "glm.hpp"

#include "Particle.h"
#include "Constraints.h"



class Cloth {

	int particleWidth;
	int particleHeight;

	std::vector<Particle> particles;
	std::vector<Constraint> constraints;

	Particle* getParticle(int x, int y) { return &particles[y*particleWidth + x]; }
	void makeConstraint(Particle *p1, Particle *p2) { constraints.push_back(Constraint(p1, p2)); }

};


