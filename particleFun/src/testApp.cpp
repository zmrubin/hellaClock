#include "testApp.h"
#include "particle.h"
//--------------------------------------------------------------

Canvas * canvas;

void testApp::setup()
{
    #ifdef RPI
    rgbThread.startThread(false, false);
    #endif
/*
    GPIO io;
    if(!io.Init()){
        printf("IO ERROR: are you root?");
        return;
    }
    canvas = new RGBMatrix(&io, 32,2);
    canvas->Fill(0,0,255);
  
    int center_x = canvas->width() / 2;
      int center_y = canvas->height() / 2;
        float radius_max = canvas->width() / 2;
          float angle_step = 1.0 / 360;
            for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step) {
                float dot_x = cos(a * 2 * M_PI) * r;
                    float dot_y = sin(a * 2 * M_PI) * r;
                        rgbThread.setPixel(center_x + dot_x, center_y + dot_y,
                                             255, 0, 0);
                                                 usleep(1 * 100);  // wait a little to slow down things.
}
*/


    //make a list of 100 particles
    
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
    printf("%f\n",normFactor);
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
    
    rgbThread.clear();
    vector<Particle*>::iterator it;
    for(it=universe.particles.begin(); it != universe.particles.end(); it++)
    {
        #ifdef RPI
        rgbThread.setPixel((*it)->pos.x, (*it)->pos.y, 255,255,255);
        #else
        ofCircle((*it)->pos,1);
        #endif // RPI
    }

//    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);





   /* vector<ofVec2f*>::iterator it;
    for(it=chargePoints.begin(); it != chargePoints.end(); it++)
    {

   ofCircle((*it)->x, (*it)->y,1); }*/
}
testApp::~testApp(){
    #ifdef RPI
    rgbThread.stopThread();
   // canvas->Clear();
  // delete canvas;
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
