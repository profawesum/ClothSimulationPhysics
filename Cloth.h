//lib includes
#include <glut.h> 
#include <math.h>
#include <vector>
#include <iostream>
#include "glm.hpp"


using namespace glm;


class Particle {

public:

	bool movable;
	float mass;

	vec3 pos;
	vec3 oldPos;
	vec3 acceleration;
	vec3 accumulatedNormal;

	//constructor
	Particle(vec3 pos) : pos(pos), oldPos(pos), acceleration(vec3(0, 0, 0)), mass(1), movable(true), accumulatedNormal(vec3(0, 0, 0)) {}
	Particle() {}

	vec3& getPos() { return pos; }

	void addForce(vec3 f) { acceleration += f / mass; }

	void resetAcceleration() { acceleration = vec3(0, 0, 0); }

	void offsetPos(const vec3 v) { if (movable) pos += v; }

	void makeUnmovable() { movable = false; }

	void addToNormal(vec3 normal) { accumulatedNormal += normalize(normal); }

	vec3 getNormal() { return accumulatedNormal; }

	void resetNormal() { accumulatedNormal = vec3(0, 0, 0); }

	void timeStep();

};


class Constraint {


private:
	float restDistance;

public:
	Particle *p1, *p2;


	Constraint(Particle *p1, Particle *p2);

	void satisfyConstraint();

};


class Cloth{

public:

	int particleWidth;
	int particleHeight;

	std::vector<Particle> particles;
	std::vector<Constraint> constraints;

	Particle* getParticle(int x, int y) { return &particles[y*particleWidth + x]; }

	void makeConstraint(Particle *p1, Particle *p2) { constraints.push_back(Constraint(p1, p2)); }

	glm::vec3 calcTriangleNorm(Particle *p1, Particle *p2, Particle *p3);
	void addWindForce(Particle *p1, Particle *p2, Particle *p3, const glm::vec3 direction);

	void drawTriangle(Particle *p1, Particle *p2, Particle *p3, glm::vec3 color);

	Cloth(float width, float height, int numParticlesWidth, int numParticlesHeight);

	void drawShaded();

	void timeStep();

	void addForce(const glm::vec3 direction);

	void windForce(const glm::vec3 direction);

	void ballCollision(const glm::vec3 center, const float radius);


};


extern float Damping;
extern float TimeStepSize;
extern float ConstraintIterations;


