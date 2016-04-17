#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H
#include <iostream>
#include <vecmath.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <windows.h>
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include "particleSystem.h"

using namespace std;

class PendulumSystem: public ParticleSystem
{
public:
	PendulumSystem(int numParticles);
	
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();
    
    vector<vector<int>> particleLinks;
    vector<float> mass;
    
    Vector3f gravitationalForce(float mass);
    Vector3f dragForce(Vector3f velocity);
    Vector3f springForce(Vector3f point, Vector3f parentPoint);
    
};

#endif
