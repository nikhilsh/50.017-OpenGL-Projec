#ifndef POOLSYSTEM_H
#define POOLSYSTEM_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <windows.h>
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include <vecmath.h>
#include <vector>

#include "particleSystem.h"

using namespace std;

class PoolSystem: public ParticleSystem
{
public:
	PoolSystem(int numParticles);
	
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();

protected:
    vector<Vector3f> m_boundaries;
    
};

#endif
