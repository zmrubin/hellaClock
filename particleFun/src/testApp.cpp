#include "testApp.h"
#include "particle.h"
//--------------------------------------------------------------


void testApp::setup()
{

    //make a list of 100 particles


    ofBackground(0,0,0);
    for(int i = 0; i<PARTICLE_COUNT; i++ )
    {
        int charge;
        if(ofRandom(1.0) > .5)
            charge = 1;
        else
            charge = -1;
        Particle * newPart = new Particle(ofRandomWidth(), ofRandomHeight(), 3, charge, 0.015);
        universe.particles.push_back(newPart);
    }
}

//--------------------------------------------------------------
void testApp::update()
{
   /*for(int j = 0; j<PARTICLE_COUNT; j++ )
    {
        universe.particles[j].setForce(0,0);

    }*/

    // update the time
    static float lastTime = 0;

    if(ofGetElapsedTimef() - lastTime > 1.0)
    {
        lastTime = ofGetElapsedTimef();
      //  printf("N = %i \n size = %i\n\n", n, chargePoints.size());
            string time = ofGetTimestampString("%h:%M:%S");
            universe.refString(time);

    }

        universe.update();

}

//--------------------------------------------------------------
void testApp::draw()
{
    vector<Particle*>::iterator it;

    for(it=universe.particles.begin(); it != universe.particles.end(); it++)
    {
        ofCircle((*it)->pos,1);
    }

    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);





   /* vector<ofVec2f*>::iterator it;
    for(it=chargePoints.begin(); it != chargePoints.end(); it++)
    {

   ofCircle((*it)->x, (*it)->y,1); }*/
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
