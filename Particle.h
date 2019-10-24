
//lib includes
#include <glut.h> 
#include <math.h>
#include <vector>
#include <iostream>
#include "glm.hpp"

using namespace glm;

//class Particle{
//
//public:
//
//	bool movable;
//	float mass;
//
//	vec3 pos;
//	vec3 oldPos;
//	vec3 acceleration;
//	vec3 accumulatedNormal;
//
//	//constructor
//	Particle(vec3 pos) : pos(pos), oldPos(pos), acceleration(vec3(0, 0, 0)), mass(1), movable(true), accumulatedNormal(vec3(0, 0, 0)) {}
//	Particle() {}
//
//	vec3& getPos() { return pos; }
//
//	void addForce(vec3 f) { acceleration += f / mass; }
//
//	void resetAcceleration() { acceleration = vec3(0, 0, 0); }
//
//	void offsetPos(const vec3 v) { if (movable) pos += v; }
//
//	void makeUnmovable() { movable = false; }
//
//	void addToNormal(vec3 normal) { accumulatedNormal += normalize(normal); }
//
//	vec3 getNormal() { return accumulatedNormal; }
//	
//	void resetNormal() { accumulatedNormal = vec3(0, 0, 0); }
//
//	void timeStep();
//
//};
//
//extern float Damping;
//extern float TimeStepSize;
//extern float ConstraintIterations;