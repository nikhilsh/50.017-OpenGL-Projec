#include "TimeStepper.hpp"
#include <iostream>

///TODO: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
    int numParticles = particleSystem->m_numParticles;
    
    vector<Vector3f> currentState = particleSystem->getState();
    vector<Vector3f> derivative = particleSystem->evalF(currentState);
    
    int statesForEachParticle = currentState.size()/numParticles;
    
    cout << "currentState.size():\t" << currentState.size() << endl;
    cout << "numParticles:\t" << numParticles << endl;
    
    vector<Vector3f> newState;
    
    for (int i=0 ; i<currentState.size(); i+=statesForEachParticle){
        for (int j=0 ; j<statesForEachParticle ; j++){
            newState.push_back( currentState[i+j] + (stepSize*derivative[i+j]) );
            cout << "j=" << j << "\t"
                << currentState[i+j][0] << " "
                << currentState[i+j][1] << " "
                << currentState[i+j][2] << " "
                << endl;
        }
    }
    
    particleSystem->setState(newState);
    
}

///TODO: implement Trapzoidal rule here
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
    int numParticles = particleSystem->m_numParticles;
    
    vector<Vector3f> currentState = particleSystem->getState();
    vector<Vector3f> derivative_current = particleSystem->evalF(currentState);
    
    int statesForEachParticle = currentState.size()/numParticles;
    
    cout << "currentState.size():\t" << currentState.size() << endl;
    cout << "numParticles:\t" << numParticles << endl;
    
    vector<Vector3f> newState;
    vector<Vector3f> newNewState;
    
    for (int i=0 ; i<currentState.size(); i+=statesForEachParticle){
        for (int j=0 ; j<statesForEachParticle ; j++){
            newState.push_back( currentState[i+j] + (stepSize*derivative_current[i+j]) );
            cout << "j=" << j << "\t"
            << currentState[i+j][0] << " "
            << currentState[i+j][1] << " "
            << currentState[i+j][2] << " "
            << endl;
        }
    }
    
    vector<Vector3f> derivative_future = particleSystem->evalF(newState);
    for (int i=0 ; i<currentState.size(); i+=statesForEachParticle){
        for (int j=0 ; j<statesForEachParticle ; j++){
            newNewState.push_back( currentState[i+j] + (stepSize/2)*(derivative_current[i+j]+derivative_future[i+j]) );
        }
    }
    
    particleSystem->setState(newNewState);
}


void RK4::takeStep(ParticleSystem* particleSystem, float stepSize)
{
    int numParticles = particleSystem->m_numParticles;
    
    vector<Vector3f> k0_state = particleSystem->getState();
    int statesForEachParticle = k0_state.size()/numParticles;
    
    vector<Vector3f> k1 = particleSystem->evalF(k0_state);
    vector<Vector3f> k1_state;
    for (int i=0 ; i<k0_state.size(); i+=statesForEachParticle){
        for (int j=0 ; j<statesForEachParticle ; j++){
            k1_state.push_back( k0_state[i+j] + ((stepSize/2.0f)*k1[i+j]) );
        }
    }
    
    vector<Vector3f> k2 = particleSystem->evalF(k1_state);
    vector<Vector3f> k2_state;
    for (int i=0 ; i<k0_state.size(); i+=statesForEachParticle){
        for (int j=0 ; j<statesForEachParticle ; j++){
            k2_state.push_back( k0_state[i+j] + ((stepSize/2.0f)*k2[i+j]) );
        }
    }
    
    vector<Vector3f> k3 = particleSystem->evalF(k2_state);
    vector<Vector3f> k3_state;
    for (int i=0 ; i<k0_state.size(); i+=statesForEachParticle){
        for (int j=0 ; j<statesForEachParticle ; j++){
            k3_state.push_back( k0_state[i+j] + (stepSize*k3[i+j]) );
        }
    }
    
    vector<Vector3f> k4 = particleSystem->evalF(k3_state);
    
    vector<Vector3f> newState;
    for (int i=0 ; i<k0_state.size(); i+=statesForEachParticle){
        for (int j=0 ; j<statesForEachParticle ; j++){
            newState.push_back( k0_state[i+j] +
                               (stepSize*(k1[i+j]+2*k2[i+j]+2*k3[i+j]+k4[i+j])/6.0)
                               );
        }
    }
    
    particleSystem->setState(newState);
}











