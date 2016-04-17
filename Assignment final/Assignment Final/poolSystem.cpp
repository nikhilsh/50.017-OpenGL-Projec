
#include "poolSystem.h"

using namespace std;

PoolSystem::PoolSystem(int numParticles):ParticleSystem(numParticles)
{
    m_numParticles = numParticles;
    
//    m_vVecState.push_back(Vector3f(0.1f,0.1f,0.0f));
//    initState = m_vVecState;
//    setState(initState);
    
    // initialise boundaries
    m_boundaries.push_back( Vector3f(-4.0f, 0.0f, -5.0f) );
    m_boundaries.push_back( Vector3f(-4.0f, 0.0f, 5.0f) );
    m_boundaries.push_back( Vector3f(4.0f, 0.0f, -5.0f) );
    m_boundaries.push_back( Vector3f(4.0f, 0.0f, 5.0f) );
    
    // initialise 3 pool balls
    // {position, velocity, position, velocity, etc...}
    m_vVecState.push_back(Vector3f(0.0f,-5.0f,-2.5f));
    m_vVecState.push_back(Vector3f());
    m_vVecState.push_back(Vector3f(-2.0f,-5.0f,-2.5f));
    m_vVecState.push_back(Vector3f());
    m_vVecState.push_back(Vector3f(2.0f,-5.0f,-2.5f));
    m_vVecState.push_back(Vector3f());
    
    initState = m_vVecState;
    setState(initState);
    
    
}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PoolSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	// YOUR CODE HERE
    
    for (int i=0 ; i< state.size() ; i+=2){
        f.push_back(state[i+1]); // differentiate position == velocity
        
        // calculate original force - drag force - recoil force == acceleration;
        
    }

	return f;
}

// render the system (ie draw the particles)
void PoolSystem::draw()
{
    
    vector<Vector3f> pos = getState();
    for (int i=0 ; i<pos.size() ; i+=2){
        glPushMatrix();
        glTranslatef(pos[i][0], pos[i][1], pos[i][2] );
        glutSolidSphere(0.5f,30.0f,30.0f);
        glPopMatrix();
    }
    
}




