
//lib includes
#include <glut.h> 
#include <math.h>
#include <vector>
#include <iostream>
#include "glm.hpp"

#include "Particle.h"


class Constraint {


private:
	float restDistance;

public :
	Particle *p1, *p2;


	Constraint(Particle *p1, Particle *p2);

	void satisfyConstraint();




};