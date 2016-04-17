#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include <vecmath.h>
#include <vector>
#include <iostream>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <windows.h>
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include "particleSystem.h"

class ClothSystem: public ParticleSystem
{
///ADD MORE FUNCTION AND FIELDS HERE
public:
	ClothSystem(int numParticles);
    
    float mass;
    int length;
    float particleDistance;
    
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();
    
    vector<vector<int>> structuralLinks;
    vector<vector<int>> shearLinks;
    vector<vector<int>> flexLinks;
    
    Vector3f gravitationalForce(float mass);
    Vector3f dragForce(Vector3f velocity);
    Vector3f springForce(Vector3f point, Vector3f parentPoint, float constant, float rest);
    int indexOf(int i, int j, int length);
    void drawCurve();
    vector<Vector3f> getVertexes(int steps, vector<Vector3f>controlPoints);
    int factorial(float number);
    double swing_sin = 0.0;
    

private:

};


#endif
