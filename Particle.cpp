#ifndef Particle_H
#define Particle_H


#include "Cloth.h"
#include "glm.hpp"

float Damping = 0.1f;
float TimeStepSize = 0.5*0.5;
float ConstraintIterations = 25;

void Particle::timeStep() {
	if (movable) {
		vec3 temp = pos;
		pos = pos + (pos - oldPos) * (1.0f - Damping) + acceleration * TimeStepSize;
		oldPos = temp;
		acceleration = vec3(0, 0, 0);
	}
}

#endif