#pragma once

#include "ofMain.h"

#define ADAFRUIT_RGBMATRIX_HAT
#include "led-matrix.h"
#include <unistd.h>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;


//#include "ofxTextSuite.h"

class ofRGBMatrix:public ofThread
{
    Canvas *canvas;
    void threadedFunction ()
    {
        GPIO io;
        if (!io.Init ())
        {
            printf ("IO ERROR: are you root?");
            return;
        }
        canvas = new RGBMatrix (&io, 32, 2);

        while (isThreadRunning())
        {
            continue;
        }
        canvas->Clear();
        delete canvas;
    }
public:
    void setPixel (int x, int y, int r, int g, int b)
    {
        canvas->SetPixel (x, y, r, g, b);
    }
      void setPixel (ofVec2f pos, ofColor color)
    {
        canvas->SetPixel (pos.x, pos.y, color.r, color.g, color.b);
    }
   void fill(int r, int g, int b)
    {
        canvas->Fill(r,g,b);
    }
    void clear()
    {
        canvas->Clear();
    }
};
