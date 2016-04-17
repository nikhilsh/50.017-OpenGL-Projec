
#include "pendulumSystem.h"

using namespace std;

PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	m_numParticles = numParticles;
	
	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_numParticles; i++) {
		
		// for this system, we care about the position and the velocity
        Vector3f position = Vector3f( 1.0f*i, 0.0f, 0.0f );
        Vector3f velocity = Vector3f( 0.0f, 0.0f, 0.0f );
        initState.push_back( position );
        initState.push_back( velocity );
        
        /* 
         documenting down then links between particles
         particleLinks = 
            {   {1},    //first particle
                {0,2},  //second particle
                {1,3},  //third particle
                ...     //rest of the particles
                {x}     //last particle
            }
         */
        if ( i==0 ){
            // first particle, link to 2nd particle
            vector<int> temp;
            temp.push_back(1);
            particleLinks.push_back(temp);
            mass.push_back(10.0f);
        } else if( i==(numParticles-1) ){
            // last particle, link to 2nd last particle
            vector<int> temp;
            temp.push_back(i-1);
            particleLinks.push_back(temp);
            mass.push_back(10.0f);
        } else{
            // middle particles, link to front and back
            vector<int> temp;
            temp.push_back(i-1);
            temp.push_back(i+1);
            particleLinks.push_back(temp);
            mass.push_back(10.0f);
        }
	}
    setState(initState);
    
    
    // System initalisation messages
    cout << "initalising pendulum system" << endl;
    cout << "particle count: \t" << m_numParticles << endl;
    cout << "states count: \t\t" << getState().size()/2 << endl;
    cout << "particle links count: \t" << particleLinks.size() << endl;
    cout << "mass count \t\t" << mass.size() << endl;
    cout << "links listing" << endl;
    for (int i=0 ; i<particleLinks.size() ; i++){
        cout << "particle " << i << ":\t";
        for (int j=0 ; j<particleLinks[i].size() ; j++){
            cout << particleLinks[i][j] << "\t";
        }
        cout << endl;
    }
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;
    
	// YOUR CODE HERE
    for (int i=0 ; i<m_numParticles; i++){
        if (i == 0){
            f.push_back(Vector3f());
            f.push_back(Vector3f());
        } else {
            Vector3f x = state[i*2];
            Vector3f v = state[(i*2)+1];
            
            Vector3f force = gravitationalForce(mass[i]);
            force += dragForce(v);
            for (int j=0 ; j<particleLinks[i].size(); j++){
                int parentPointIndex = particleLinks[i][j];
                force+=springForce(x, state[parentPointIndex*2]);
            }
            
            f.push_back(v);
            f.push_back(force/mass[i]);
        }
    }
    

	return f;
}

Vector3f PendulumSystem::gravitationalForce(float mass){
    Vector3f gravity = Vector3f(0.0f, -9.81f, 0.0f);
    return mass*gravity;
}

Vector3f PendulumSystem::dragForce(Vector3f velocity){
    // "https://en.wikipedia.org/wiki/Drag_coefficient"
    float dragConstant = 10.0f;
    
    return -1.0f*dragConstant*velocity;
}

Vector3f PendulumSystem::springForce(Vector3f point, Vector3f parentPoint){
    float springConstant = 1000.0f;
    Vector3f distance = point - parentPoint;
    float restLength = 1.0f;
    
    Vector3f force = -1.0f*springConstant*(distance.abs() - restLength)* distance / distance.abs();
    
    return force;
}


// render the system (ie draw the particles)
void PendulumSystem::draw()
{
    vector<Vector3f> state = getState();
	for (int i = 0; i < m_numParticles; i++) {
		//  position of particle i. YOUR CODE HERE
        Vector3f pos = state[i*2];
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
}
