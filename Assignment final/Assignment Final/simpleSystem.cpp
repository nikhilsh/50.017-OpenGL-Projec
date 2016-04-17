
#include "simpleSystem.h"

using namespace std;

SimpleSystem::SimpleSystem(int numParticles):ParticleSystem(numParticles)
{
    
    m_numParticles = numParticles;
    m_vVecState.push_back(Vector3f(0.1f,0.1f,0.0f));
    initState = m_vVecState;
    setState(initState);
    
}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> SimpleSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	// YOUR CODE HERE
    
    for (int i=0 ; i< state.size() ; i++){
//        Vector3f temp;
//        temp[0] = -1 * state[i][1];
//        temp[1] = state[i][0];
//        temp[2] = 0;
//        f.push_back(temp);
//        
        f.push_back(differentiatePoint(state[i]));
    }

	return f;
}

// render the system (ie draw the particles)
void SimpleSystem::draw()
{
//    Vector3f pos = getState()[0] ;//YOUR PARTICLE POSITION
//    glPushMatrix();
//    glTranslatef(pos[0], pos[1], pos[2] );
//    glutSolidSphere(0.075f,10.0f,10.0f);
//    glPopMatrix();
    
    vector<Vector3f> pos = getState();
    for (int i=0 ; i<pos.size() ; i++){
        glPushMatrix();
        glTranslatef(pos[i][0], pos[i][1], pos[i][2] );
        glutSolidSphere(0.1f,10.0f,10.0f);
        glPopMatrix();
    }
    
    
}




