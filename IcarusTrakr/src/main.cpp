#include "testApp.h"
#include "ofAppGlutWindow.h"
//#include "ofAppNoWindow.h"

//--------------------------------------------------------------
int main()
{
ofSetLogLevel(OF_LOG_SILENT);
//ofSetLogLevel(OF_LOG_VERBOSE);
#ifndef RPI
    ofAppGlutWindow window; // create a window
    ofSetupOpenGL(&window, 64*1, 32*1, OF_WINDOW);
    // RPI
    // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
#else
 //  ofAppNoWindow window;
    ofSetupOpenGL( 64*1, 32*1, OF_WINDOW);
#endif
    ofRunApp(new testApp()); // start the app
}

