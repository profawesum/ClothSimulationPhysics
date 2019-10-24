#include "Cloth.h"
//#include "Particle.h"

Cloth::Cloth(float width, float height, int numParticlesWidth, int numParticlesHeight) {

	particles.resize(numParticlesWidth*numParticlesHeight); //I am essentially using this vector as an array with room for num_particles_width*num_particles_height particles

		// creating particles in a grid of particles from (0,0,0) to (width,-height,0)
	for (int x = 0; x < numParticlesWidth; x++)
	{
		for (int y = 0; y < numParticlesHeight; y++)
		{
			glm::vec3 pos = glm::vec3(width * (x / (float)numParticlesWidth),
				-height * (y / (float)numParticlesHeight),
				0);
			particles[y*numParticlesWidth + x] = Particle(pos); // insert particle in column x at y'th row
		}
	}

	// Connecting immediate neighbor particles with constraints (distance 1 and sqrt(2) in the grid)
	for (int x = 0; x < numParticlesWidth; x++)
	{
		for (int y = 0; y < numParticlesHeight; y++)
		{
			if (x < numParticlesWidth - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y));
			if (y < numParticlesHeight - 1) makeConstraint(getParticle(x, y), getParticle(x, y + 1));
			if (x < numParticlesWidth - 1 && y < numParticlesHeight - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y + 1));
			if (x < numParticlesWidth - 1 && y < numParticlesHeight - 1) makeConstraint(getParticle(x + 1, y), getParticle(x, y + 1));
		}
	}


	// Connecting secondary neighbors with constraints (distance 2 and sqrt(4) in the grid)
	for (int x = 0; x < numParticlesWidth; x++)
	{
		for (int y = 0; y < numParticlesHeight; y++)
		{
			if (x < numParticlesWidth - 2) makeConstraint(getParticle(x, y), getParticle(x + 2, y));
			if (y < numParticlesHeight - 2) makeConstraint(getParticle(x, y), getParticle(x, y + 2));
			if (x < numParticlesWidth - 2 && y < numParticlesHeight - 2) makeConstraint(getParticle(x, y), getParticle(x + 2, y + 2));
			if (x < numParticlesWidth - 2 && y < numParticlesHeight - 2) makeConstraint(getParticle(x + 2, y), getParticle(x, y + 2));
		}
	}


	// making the upper left most three and right most three particles unmovable
	for (int i = 0; i < 3; i++)
	{
		getParticle(0 + i, 0)->offsetPos(glm::vec3(0.5, 0.0, 0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
		getParticle(0 + i, 0)->makeUnmovable();

		getParticle(0 + i, 0)->offsetPos(glm::vec3(-0.5, 0.0, 0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
		getParticle(numParticlesWidth - 1 - i, 0)->makeUnmovable();
	}

}


glm::vec3 Cloth::calcTriangleNorm(Particle *p1, Particle *p2, Particle *p3) {

	glm::vec3 pos1 = p1->getPos();
	glm::vec3 pos2 = p2->getPos();
	glm::vec3 pos3 = p3->getPos();

	glm::vec3 v1 = pos2 - pos1;
	glm::vec3 v2 = pos3 - pos1;

	return cross(v1, v2);

}

void Cloth::addWindForce(Particle *p1, Particle *p2, Particle *p3, const glm::vec3 direction) {

	glm::vec3 normal = calcTriangleNorm(p1, p2, p3);
	glm::vec3 d = normalize(normal);
	glm::vec3 force = normal * (dot(d, direction));
	p1->addForce(force);
	p2->addForce(force);
	p3->addForce(force);

}

void Cloth::drawTriangle(Particle *p1, Particle *p2, Particle *p3, glm::vec3 color) {

	glColor3fv((GLfloat*)&color);

	glNormal3fv((GLfloat *) &(normalize((p1->getNormal()))));
	glVertex3fv((GLfloat *) &(p1->getPos()));

	glNormal3fv((GLfloat *) &(normalize((p2->getNormal()))));
	glVertex3fv((GLfloat *) &(p2->getPos()));

	glNormal3fv((GLfloat *) &(normalize((p3->getNormal()))));
	glVertex3fv((GLfloat *) &(p3->getPos()));

}

void Cloth::drawShaded() {

	// reset normals (which where written to last frame)
	std::vector<Particle>::iterator particle;
	for (particle = particles.begin(); particle != particles.end(); particle++)
	{
		(*particle).resetNormal();
	}

	//create smooth per particle normals by adding up all the (hard) triangle normals that each particle is part of
	for (int x = 0; x < particleWidth - 1; x++)
	{
		for (int y = 0; y < particleHeight - 1; y++)
		{
			glm::vec3 normal = calcTriangleNorm(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1));
			getParticle(x + 1, y)->addToNormal(normal);
			getParticle(x, y)->addToNormal(normal);
			getParticle(x, y + 1)->addToNormal(normal);

			normal = calcTriangleNorm(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1));
			getParticle(x + 1, y + 1)->addToNormal(normal);
			getParticle(x + 1, y)->addToNormal(normal);
			getParticle(x, y + 1)->addToNormal(normal);
		}
	}

	glBegin(GL_TRIANGLES);
	for (int x = 0; x < particleWidth - 1; x++)
	{
		for (int y = 0; y < particleHeight - 1; y++)
		{
			glm::vec3 color(0, 0, 0);
			if (x % 2) // red and white color is interleaved according to which column number
				color = glm::vec3(0.6f, 0.2f, 0.2f);
			else
				color = glm::vec3(1.0f, 1.0f, 1.0f);

			drawTriangle(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1), color);
			drawTriangle(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1), color);
		}
	}
	glEnd();
}

void Cloth::timeStep() {

	std::vector<Constraint>::iterator constraint;
	for (int i = 0; i < ConstraintIterations; i++) // iterate over all constraints several times
	{
		for (constraint = constraints.begin(); constraint != constraints.end(); constraint++)
		{
			(*constraint).satisfyConstraint(); // satisfy constraint.
		}
	}

	std::vector<Particle>::iterator particle;
	for (particle = particles.begin(); particle != particles.end(); particle++)
	{
		(*particle).timeStep(); // calculate the position of each particle at the next time step.
	}
}

void Cloth::addForce(glm::vec3 direction) {

	std::vector<Particle>::iterator particle;
	for (particle = particles.begin(); particle != particles.end(); particle++)
	{
		(*particle).addForce(direction); // add the forces to each particle
	}

}

void Cloth::windForce(glm::vec3 direction) {
	for (int x = 0; x < particleWidth - 1; x++)
	{
		for (int y = 0; y < particleHeight - 1; y++)
		{
			addWindForce(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1), direction);
			addWindForce(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1), direction);
		}
	}
}

void Cloth::ballCollision(const glm::vec3 center, const float radius)
{
	std::vector<Particle>::iterator particle;
	for (particle = particles.begin(); particle != particles.end(); particle++)
	{
		glm::vec3 v = (*particle).getPos() - center;
		float l = v.length();
		if (v.length() < radius) // if the particle is inside the ball
		{
			(*particle).offsetPos(normalize(v)*(radius - l)); // project the particle to the surface of the ball
		}
	}
}