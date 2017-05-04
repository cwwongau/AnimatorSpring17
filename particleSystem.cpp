#pragma warning(disable : 4786)

#include "particleSystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <cmath>
#include <climits>
#include <ctime>
#include <iostream>

using namespace std;


/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() : bake_fps(30), simulate(false), dirty(false), particleNum(500), pLife(2), mass(1.0), currentTime(0.0)
{
	srand(time(0));

	// add the controlling forces
	forces.push_back(new Gravity(Vec3f(0, -0.02, 0)));
}


/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	particles.clear();
	forces.clear();
}


/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
	bake_end_time = -1;
	simulate = true;
	dirty = true;
}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
	simulate = false;
	dirty = true;
}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
	simulate = false;
	dirty = true;
}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
	bake_fps = t - currentTime;
	currentTime = t;
	if (simulate) {
		map<float, vector<Particle>>::iterator it = bakedParticles.find(t);
		if (it == bakedParticles.end()) {	// not baked, need simulation
			for (vector<Particle>::iterator iter = particles.begin(); iter != particles.end(); iter++) {
				iter->move(bake_fps);
			}
			bakeParticles(t);
		}
		else {
			particles = bakedParticles[t];
		}
	}
}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	if (simulate) {
		for (vector<Particle>::iterator iter = bakedParticles[t].begin(); iter != bakedParticles[t].end(); iter++) {
			iter->draw();
		}
	}
}

/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{
	bakedParticles.insert(pair<float, vector<Particle>>(t, particles));
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	bakedParticles.clear();
}





