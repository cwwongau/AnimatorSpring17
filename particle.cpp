#include "particle.h"
// SAMPLE_SOLUTION

Particle::Particle(Vec3f pos, float m, float t) : position(pos), mass(m), lifeSpan(t) {}

Particle::Particle(Vec3f pos, Vec3f v,float m, float t) : position(pos), velocity(v), mass(m), lifeSpan(t) {}

void Particle::addForce(Force* f) {
	this->forces.push_back(f);
}

void Particle::move(float delta, Vec3f wp) {
	for (vector<Force*>::iterator iter = forces.begin(); iter != forces.end(); iter++) {
		(*iter)->applyTo(this->velocity, delta, wp);
	}
	this->position += this->velocity * delta;
}

void Particle::draw() {
	setDiffuseColor(0, 1, 0);
	glPointSize(2.5);
	glPushMatrix();
		glBegin(GL_POINTS);
		glVertex3f(position[0], position[1], position[2]);
		glEnd();
	glPopMatrix();
}