#pragma once
/* some fun ideas:
particles attached on springs to points on a number
particles forming a number, whose integrator reference changes
charged particles, avoiding time region
*/
//#define RPI
#include "ofMain.h"
#include "universe.h"

#ifdef RPI
#include "ofRGBMatrix.h"
#define ADAFRUIT_RGBMATRIX_HAT
#include "led-matrix.h"
#include <unistd.h>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
#endif // RPI

//#include "ofxTextSuite.h"
#define PARTICLE_COUNT 200

#ifdef RPI
//Canvas *canvas;
#endif // RPI

class testApp : public ofBaseApp
{
public:
    #ifdef RPI
    ofRGBMatrix rgbThread;
    #endif
     ofImage brcMap;
    Universe universe;
    float normFactor = 1;
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    ~testApp();
};
