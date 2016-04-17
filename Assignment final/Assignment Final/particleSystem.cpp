#include "particleSystem.h"

ParticleSystem::ParticleSystem(int nParticles):m_numParticles(nParticles){
    
}

Vector3f ParticleSystem::differentiatePoint(Vector3f point){
    
    return Vector3f(-1*point[2], 0, point[0]);
}

//vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)