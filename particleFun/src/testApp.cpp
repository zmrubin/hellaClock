#include "testApp.h"
#include "particle.h"
//--------------------------------------------------------------



void testApp::setup()
{
#ifdef RPI
    rgbThread.startThread(false, false);
#endif

  /*
    canvas->Fill(0,0,255);

    int center_x = canvas->width() / 2;
    int center_y = canvas->height() / 2;
    float radius_max = canvas->width() / 2;
    float angle_step = 1.0 / 360;
    for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step)
    {
        float dot_x = cos(a * 2 * M_PI) * r;
        float dot_y = sin(a * 2 * M_PI) * r;
        rgbThread.setPixel(center_x + dot_x, center_y + dot_y,
                           255, 0, 0);
        usleep(1 * 100);  // wait a little to slow down things.
    }

*/
    //make a list of 100 particles
    receive.setup(OSCPORT);
    globalBrightness = 1.0;
   ofBackground(0,0,0);
    for(int i = 0; i<PARTICLE_COUNT; i++ )
    {
        int charge;
        if(ofRandom(1.0) > .5)
            charge = 1;
        else
            charge = -1;
        Particle * newPart = new Particle(ofRandomWidth(), ofRandomHeight(), 1, charge, 0.02);
        universe.particles.push_back(newPart);
    }
}

//--------------------------------------------------------------
float testApp::colorMag[6] = {1.0};
void testApp::update()
{
  while(receive.hasWaitingMessages()){
    ofxOscMessage m; 
    receive.getNextMessage(&m);
//     printf(m.getAddress().c_str());
    if(m.getAddress() == "/Knob3/x"){
     globalBrightness= m.getArgAsFloat(0);
     }
    if(m.getAddress() == "/Range/red"){
     colorMag[0] = m.getArgAsFloat(0);
     colorMag[1] = m.getArgAsFloat(1);
     }
     if(m.getAddress() == "/Range/green"){
     colorMag[2] = m.getArgAsFloat(0);
     colorMag[3] = m.getArgAsFloat(1);
     }
   if(m.getAddress() == "/Range/blue"){
     colorMag[5] = m.getArgAsFloat(0);
     colorMag[5] = m.getArgAsFloat(1);
     }
  
  }

    static float normFactor = 1;
    static float lastTime = 0;
    if(ofGetElapsedTimef() - lastTime > 3.0)
    {
        printf("%f %f\n",ofGetFrameRate(),globalBrightness );
        lastTime = ofGetElapsedTimef();
        string time = ofGetTimestampString("%h:%M:%S");
        universe.refString(time);
    }
    universe.update();

}

//--------------------------------------------------------------
void testApp::draw()
{
#ifdef RPI
    rgbThread.clear();
#endif // RPI
    vector<Particle*>::iterator it;
    for(it=universe.particles.begin(); it != universe.particles.end(); it++)
    {
#ifdef RPI
        ofColor pColor = (*it)->color;
        pColor.r *= globalBrightness * ofRandom (colorMag[0], colorMag[1]);
        pColor.g *= globalBrightness * ofRandom (colorMag[2], colorMag[3]);
        pColor.b *= globalBrightness * ofRandom (colorMag[4], colorMag[5]);
        rgbThread.setPixel((*it)->pos,pColor );
#else
        ofCircle((*it)->pos,1);
#endif // RPI
    }

}
testApp::~testApp()
{
#ifdef RPI
    rgbThread.stopThread();
#endif // RPI
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
