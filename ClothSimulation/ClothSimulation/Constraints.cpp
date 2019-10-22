#include "Constraints.h"
#include "glm.hpp"

Constraint::Constraint(Particle *p1, Particle *p2) {
	vec3 vec = p1->getPos() - p2->getPos();
	restDistance = vec.length();
}

void Constraint::satisfyConstraint() {

	vec3 p1Top2 = p2->getPos() - p1->getPos();

}