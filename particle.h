#ifndef __PARTICLE__H__
#define __PARTICLE__H__

#include "modelerglobals.h"
#include "vec.h"


class particle {
public:
	particle(Vec3f pos, Vec3f vel, float life);
	~particle() {};

	Vec3f getPosition() { return position; };
	Vec3f getVelocity() {return velocity; };
	float getTimeAlive() {return timeAlive; };
	float getLifeSpan() { return lifeSpan; };

	void setPosition(Vec3f pos) { position = pos; };
	void setVelocity(Vec3f vel) { velocity = vel; };
	void setTimeAlive(float time) { timeAlive = time; };

private:
	Vec3f position;
	Vec3f velocity;
	float timeAlive;
	float lifeSpan;

};

#endif