#include "testApp.h"
#include "ofAppGlutWindow.h"

#define RPI
//--------------------------------------------------------------
int main(){
  #ifndef RPI
    ofAppGlutWindow window; // create a window
       // RPI
        // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
            ofSetupOpenGL(&window, 64*1, 32*1, OF_WINDOW);
              #else
                ofSetupOpenGL(64*1, 32*1, OF_WINDOW);
                  #endif
                    ofRunApp(new testApp()); // start the app
                    }

