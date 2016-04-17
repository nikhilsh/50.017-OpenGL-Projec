#include "ClothSystem.h"

using namespace std;

//TODO: Initialize here
ClothSystem::ClothSystem(int numParticles):ParticleSystem(numParticles)
{
    m_numParticles = numParticles; //specifies the total of particles on each side of the cloth/mesh.
    mass = 10.0f;
    length = sqrt(m_numParticles);
    wind = false;
    particleDistance = 1.0f;
    wireframe = true;
    swing = false;
    swing_sin = 0.0;
    
    
    // check whether its a square
    if (fmod(m_numParticles*1.0f, 1.0f) != 0.0f){
        cout << "number of particles specified cannot form a square mesh" << endl;
        exit(0);
    }
    
    // initalising square mesh. m_numParticles x m_numParticles
    for (int i=0 ; i<sqrt(numParticles) ; i++){
        for (int j=0 ; j<sqrt(numParticles) ; j++){
            Vector3f position = Vector3f(particleDistance*i, 0.0f, particleDistance*j);
            Vector3f velocity = Vector3f(0.0f, 0.0f, 0.0f);
            initState.push_back(position);
            initState.push_back(velocity);
            
            vector<int> tempStructuralLinks;
            if (i != 0){
                tempStructuralLinks.push_back(indexOf(i-1, j, sqrt(m_numParticles)));
            }
            if (i != sqrt(numParticles)-1){
                tempStructuralLinks.push_back(indexOf(i+1, j, sqrt(m_numParticles)));
            }
            if (j != 0){
                tempStructuralLinks.push_back(indexOf(i, j-1, sqrt(m_numParticles)));
            }
            if (j != sqrt(numParticles)-1){
                tempStructuralLinks.push_back(indexOf(i, j+1, sqrt(m_numParticles)));
            }
            structuralLinks.push_back(tempStructuralLinks);
            
            vector<int> tempShearLinks;
            if (i!=0 && j!=0){
                tempShearLinks.push_back(indexOf(i-1, j-1, length));
            }
            if (i!=0 && j!= (length-1)){
                tempShearLinks.push_back(indexOf(i-1,j+1,length));
            }
            if (i!=(length-1) && j!=0){
                tempShearLinks.push_back(indexOf(i+1,j-1,length));
            }
            if (i!=(length-1) && j!=(length-1)){
                tempShearLinks.push_back(indexOf(i+1,j+1,length));
            }
            shearLinks.push_back(tempShearLinks);
            
            vector<int> tempFlexLinks;
            if (i>1){ //up
                tempFlexLinks.push_back(indexOf(i-2,j, length));
            }
            if (i<(length-2)){ //down
                tempFlexLinks.push_back(indexOf(i+2, j, length));
            }
            if (j>1){
                tempFlexLinks.push_back(indexOf(i,j-2,length));
            }
            if (j<(length-2)){
                tempFlexLinks.push_back(indexOf(i, j+2, length));
            }
            flexLinks.push_back(tempFlexLinks);
            
        }
    }
    setState(initState);
}

int ClothSystem::indexOf(int i, int j, int length){
    return (i*length)+j;
}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
{
    vector<Vector3f> f;
    
    // YOUR CODE HERE
    for (int i=0 ; i<m_numParticles; i++){
        if (i == 0 || i==length-1){
            if (swing){
                f.push_back(Vector3f(5*cos(swing_sin), 0.0f, 0.0f));
                f.push_back(Vector3f(5*cos(swing_sin), 0.0f, 0.0f));
                swing_sin += 0.01;
                
            } else {
                f.push_back(Vector3f());
                f.push_back(Vector3f());
            }
            
        } else {
            Vector3f x = state[i*2];
            Vector3f v = state[(i*2)+1];
            
            Vector3f force = gravitationalForce(mass);
            force += dragForce(v);
            for (int j=0 ; j<structuralLinks[i].size(); j++){
                int parentPointIndex = structuralLinks[i][j];
                force+=springForce(x, state[parentPointIndex*2],1000.0f, particleDistance);
            }
            for (int j=0 ; j<shearLinks[i].size(); j++){
                int parentPointIndex = shearLinks[i][j];
                force+=springForce(x, state[parentPointIndex*2],1000.0f, sqrt(particleDistance*particleDistance + particleDistance*particleDistance));
            }
            for (int j=0 ; j<flexLinks[i].size(); j++){
                int parentPointIndex = flexLinks[i][j];
                force+=springForce(x, state[parentPointIndex*2],1000.0f, particleDistance*2);
            }
            
            if (wind){
                force+=Vector3f(-500.0f*(rand()) / (static_cast <float> (RAND_MAX)), 0.0f, 0.0f);
            }
            
            f.push_back(v);
            f.push_back(force/mass);
        }
    }
    
    return f;
}

///TODO: render the system (ie draw the particles)
void ClothSystem::draw()
{
    vector<Vector3f> state = getState();
    if (wireframe){
        
        for (int i = 0; i < m_numParticles; i++) {
            //  position of particle i. YOUR CODE HERE
            Vector3f pos = state[i*2];
            glPushMatrix();
            glTranslatef(pos[0], pos[1], pos[2] );
            glutSolidSphere(particleDistance/10,10.0f,10.0f);
            glPopMatrix();
        }
        
        for (int i=0 ; i<m_numParticles; i++){
            for (int j=0 ; j<structuralLinks[i].size(); j++){
                int parentPointIndex = structuralLinks[i][j];
                Vector3f childPos = state[i*2];
                Vector3f parentPos = state[parentPointIndex*2];
                
                glBegin(GL_LINES);
                glVertex3f(childPos[0], childPos[1], childPos[2]);
                glVertex3f(parentPos[0], parentPos[1], parentPos[2]);
                glEnd();
            }
        }
    } else {
        drawCurve();
    }
}

void ClothSystem::drawCurve(){
    vector<Vector3f> currentState = getState();
    vector<vector<Vector3f>> sets_ControlPoints;
    vector<vector<Vector3f>> sets_vertexes;
    vector<vector<Vector3f>> mesh;
    
    for (int side=0; side<length ; side++){
        vector<Vector3f> set;
        
        for (int down=0; down<length ; down++){
            set.push_back(currentState[indexOf(side,down,length)*2]);
        }
        
        sets_ControlPoints.push_back(set);
    }
    
    for (int i=0; i<sets_ControlPoints.size(); i++){
        sets_vertexes.push_back(getVertexes(200, sets_ControlPoints[i]));
    }
    
    for (int i=0 ; i<sets_vertexes[0].size() ; i++){
        vector<Vector3f> controlPoints;
        for (int j=0 ; j<sets_ControlPoints.size() ; j++){
            controlPoints.push_back(sets_vertexes[j][i]);
        }
        mesh.push_back(getVertexes(200, controlPoints));
    }
    
    
    // Save current state of OpenGL
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    
    
//    draw lines
//    glDisable( GL_LIGHTING );
//    glColor4f( 0.5f, 0.5f, 1.0f, 1.0f );
//    glLineWidth( 1 );
//    
//    for (int i=0 ; i<mesh.size(); i++){
//        glBegin( GL_LINE_STRIP );
//        for (int j=0 ; j<mesh[i].size(); j++){
//            glVertex3f( mesh[i][j][0],mesh[i][j][1],mesh[i][j][2] );
//        }
//        glEnd();
//    }
    
    // draw triangles
    glBegin(GL_TRIANGLES);
    for ( int i=0 ; i<mesh.size()-1; i++ ){
        for ( int j=0 ; j<mesh[0].size()-1 ; j++ ){
            Vector3f v1 = mesh[i][j];
            Vector3f v2 = mesh[i][j+1];
            Vector3f v3 = mesh[i+1][j];
            Vector3f v4 = mesh[i+1][j+1];
            Vector3f normal_123 = Vector3f::cross(v2-v1, v3-v1);
            Vector3f normal_324 = Vector3f::cross(v2-v3, v4-v3);
            
            glNormal3f(normal_123[0],normal_123[1],normal_123[2]);
            glVertex3f(v1[0],v1[1],v1[2]);
            glVertex3f(v2[0],v2[1],v2[2]);
            glVertex3f(v3[0],v3[1],v3[2]);
            
            glNormal3f(normal_123[0],normal_123[1],normal_123[2]);
            glVertex3f(v3[0],v3[1],v3[2]);
            glVertex3f(v2[0],v2[1],v2[2]);
            glVertex3f(v1[0],v1[1],v1[2]);
            
            glNormal3f(normal_324[0],normal_324[1],normal_324[2]);
            glVertex3f(v3[0],v3[1],v3[2]);
            glVertex3f(v2[0],v2[1],v2[2]);
            glVertex3f(v4[0],v4[1],v4[2]);
            
            glNormal3f(normal_324[0],normal_324[1],normal_324[2]);
            glVertex3f(v4[0],v4[1],v4[2]);
            glVertex3f(v2[0],v2[1],v2[2]);
            glVertex3f(v3[0],v3[1],v3[2]);
            
        }
    }
    glEnd();
    
    
    // Pop state
    glPopAttrib();
}

vector<Vector3f> ClothSystem::getVertexes(int steps, vector<Vector3f>controlPoints){
    vector<Vector3f> V_array;

    // 4 POINTS BEZIER CURVE
    for (int step=0 ; step<steps ; step++){
        float t = (step*1.0)/steps;
        float x = (1-t)*(1-t)*(1-t)*controlPoints[0][0]
        + (3*t)*(1-t)*(1-t)*controlPoints[1][0]
        + (3*t*t)*(1-t)*controlPoints[2][0]
        + t*t*t*controlPoints[3][0];
        float y = (1-t)*(1-t)*(1-t)*controlPoints[0][1]
        + (3*t)*(1-t)*(1-t)*controlPoints[1][1]
        + (3*t*t)*(1-t)*controlPoints[2][1]
        + t*t*t*controlPoints[3][1];
        float z = (1-t)*(1-t)*(1-t)*controlPoints[0][2]
        + (3*t)*(1-t)*(1-t)*controlPoints[1][2]
        + (3*t*t)*(1-t)*controlPoints[2][2]
        + t*t*t*controlPoints[3][2];
        V_array.push_back(Vector3f( x, y, z));
    }
     
    
    /* Multipoint. But does not work -.-
    for (int step=0 ; step<steps ; step++){
        float t = (step*1.0)/steps;
        
        Vector3f V = Vector3f();
        for (int i=0; i<controlPoints.size(); i++){
             float coeff = factorial(controlPoints.size()-1) /
            ( factorial(i) * factorial(controlPoints.size()-1-i) ) *
            pow(t, i) *
            pow(1-t, controlPoints.size()-1-i);
            
            V+=controlPoints[i]*coeff;
        }
        
        V_array.push_back(V);
    }
     */
    
    return V_array;
    
}

int ClothSystem::factorial(float number){
    if (number<1){
        return 1;
    }
    int result=1;
    for (int i=1; i<=number ; i++){
        result = result*i;
    }
    return number;
}

Vector3f ClothSystem::gravitationalForce(float mass){
    Vector3f gravity = Vector3f(0.0f, -9.81f, 0.0f);
    return mass*gravity;
}

Vector3f ClothSystem::dragForce(Vector3f velocity){
    // "https://en.wikipedia.org/wiki/Drag_coefficient"
    float dragConstant = 20.0f;
    
    return -1.0f*dragConstant*velocity;
}

Vector3f ClothSystem::springForce(Vector3f point, Vector3f parentPoint, float constant, float rest){
    float springConstant = constant;
    Vector3f distance = point - parentPoint;
    float restLength = rest;
    
    Vector3f force = -1.0f*springConstant*(distance.abs() - restLength)* distance / distance.abs();
    
    return force;
}
