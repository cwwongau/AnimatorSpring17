#ifndef __PARTICLE__H__
#define __PARTICLE__H__

#include "modelerglobals.h"
#include "vec.h"
#include <vector>
#include <FL/gl.h>
#include "modelerdraw.h"

class Force {
public:
	virtual void applyTo(Vec3f& speed, float val, Vec3f wp) = 0;
};

class Gravity : public Force {
public:
	Vec3f val;
	Gravity(Vec3f v) : val(v) {}
	virtual void applyTo(Vec3f& speed, float d, Vec3f wp) {
		speed += val * d;
	}
};

class Engine : public Force {
public:
	Vec3f val;
	Engine(Vec3f wp) : cp(wp), op(wp) {}
	virtual void applyTo(Vec3f& speed, float d, Vec3f wp) {
		op = cp;
		cp = wp;
		speed += op;
		speed -= cp;
		if (cp[2]-wp[2]<0 && speed[2]<cp[2] - wp[2]) speed[2] = cp[2] - wp[2];

	}
private:
	Vec3f cp;
	Vec3f op;
};



class Particle {
public:
	Particle(Vec3f p, float m, float t);
	Particle(Vec3f p, Vec3f v, float m, float t);
	~Particle() {};

	Vec3f getPosition() { return position; };
	Vec3f getVelocity() {return velocity; };
	float getTimeAlive() { return timeAlive; };
	float getLifeSpan() { return lifeSpan; };

	void setPosition(Vec3f pos) { position = pos; };
	void setVelocity(Vec3f vel) { velocity = vel; };
	void setTimeAlive(float time) { timeAlive = time; };

	void addForce(Force* f);
	void move(float delta, Vec3f wp);
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