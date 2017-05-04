#ifndef __PARTICLE__H__
#define __PARTICLE__H__

#include "modelerglobals.h"
#include "vec.h"
#include <vector>
#include <FL/gl.h>
#include "modelerdraw.h"

class Force {
public:
	virtual void applyTo(Vec3f& speed, float val) = 0;
};

class Gravity : public Force {
public:
	Vec3f val;
	Gravity(Vec3f v) : val(v) {}
	virtual void applyTo(Vec3f& speed, float d) {
		speed += val * d;
	}
};

class Particle {
public:
	Particle(Vec3f p, float m, float t);
	~Particle() {};

	Vec3f getPosition() { return position; };
	Vec3f getVelocity() {return velocity; };
	float getTimeAlive() { return timeAlive; };
	float getLifeSpan() { return lifeSpan; };

	void setPosition(Vec3f pos) { position = pos; };
	void setVelocity(Vec3f vel) { velocity = vel; };
	void setTimeAlive(float time) { timeAlive = time; };

	void addForce(Force* f);
	void move(float delta);
	void draw();

private:
	Vec3f position;
	Vec3f velocity;
	float timeAlive;
	float lifeSpan;
	float mass;
	vector<Force*> forces;

};

#endif