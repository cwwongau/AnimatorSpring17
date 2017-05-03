#pragma warning(disable : 4786)

#include "particleSystem.h"
#include "modelerdraw.h"
#include "modelerview.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <iostream>

using namespace std;


/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() : bake_fps(30), simulate(false), dirty(false), particleNum(500),pLife(2)
{
	// TODO
	cout << "PS created" << endl;
	//maxFrames = 1;
	bakedParticles = new vector<particle>[20*bake_fps];
	srand(time(0));
	pPos = Vec3f(0, 0, 0);
	for (int i = 0; i < particleNum; i++) {
		float x = (float)(((rand() % 100) - 50) / 10);
		float y = (float)(((rand() % 100) - 50) / 10);
		float z = (float)(((rand() % 100) - 50) / 10);
		particlesList.push_back(particle(pPos, Vec3f(x,y,z), pLife));
	}
	bakeParticles(0);

	

}





/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO
	//delete[] bakedParticles;
}


/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
	// TODO
	if (!simulate) {
		bake_start_time = t;
		clearBaked();
		for (t; t <= bake_end_time; t += (1 / bake_fps)) {
			computeForcesAndUpdateParticles(t);
		}
	}

	// These values are used by the UI ...
	// -ve bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	bake_end_time = -1;
	simulate = true;
	dirty = true;
	if (t >= bake_end_time) stopSimulation(t);
	startSimulation(t + 1 / bake_fps);

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
    
	// TODO
	bake_end_time = t;

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
	cout << "computing forces" << t << endl;

	// TODO
	gravityEffect = 0.3f;
	float dt = 1 / bake_fps;
	//cout << particlesList[0].getPosition()[0] << "   " << particlesList[0].getPosition()[1] << "   " << particlesList[2].getPosition()[2] << endl;
	for (int i = 0; i<particleNum; i++) {
		//update
		particlesList[i].setPosition(particlesList[i].getPosition() + particlesList[i].getVelocity() * dt);
		particlesList[i].setVelocity(particlesList[i].getVelocity() + Vec3f(0.0f, GRAVITY * gravityEffect*dt, 0.0f));
		particlesList[i].setTimeAlive(particlesList[i].getTimeAlive() + dt);
		if (particlesList[i].getTimeAlive() >= particlesList[i].getLifeSpan()) {
			float x = (float)(((rand() % 100) - 50) / 10);
			float y = (float)(((rand() % 100) - 50) / 10);
			float z = (float)(((rand() % 100) - 50) / 10);
			particlesList[i].setTimeAlive(0);
			particlesList[i].setPosition(pPos);
			particlesList[i].setVelocity(Vec3f(x, y, z));
		}

		//debug
		//cout << "Time " << t << ":" << endl << i << " : " << p.getPosition()[0] << "   " << p.getPosition()[1] << "   " << p.getPosition()[2] << "   " << endl;
	}

	bakeParticles(t);
		
	//cout << "computed" << endl;


}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	// TODO
	if (bakedParticles[(int)(t*bake_fps)].empty()) return;
	for (int i = 0; i >= 0; i--) {
		//draw
		particle p = bakedParticles[(int)(t*bake_fps)][i];
		glPushMatrix();
			glTranslated(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
			glScaled(0.1, 0.1, 0.1);
			drawBox(1, 1, 1);
		glPopMatrix();
	}

}





/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{
	bakedParticles[(int)(t*bake_fps)] = particlesList;	
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	if (bakedParticles != NULL) {
		delete[] bakedParticles;
	}

}





