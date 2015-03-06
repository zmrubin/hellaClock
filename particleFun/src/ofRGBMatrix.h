#pragma once
#define RPI
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
  Canvas *
    canvas;
 void
  threadedFunction ()
  {
    GPIO io;
    if (!io.Init ())
      {
	printf ("IO ERROR: are you root?");
	return;
      }
    canvas = new RGBMatrix (&io, 32, 2);
/*    canvas->Fill (0, 255, 0);

    int
      center_x = canvas->width () / 2;
    int
      center_y = canvas->height () / 2;
    float
      radius_max = canvas->width () / 2;
    float
      angle_step = 1.0 / 360;
    for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step)
      {
	float
	  dot_x = cos (a * 2 * M_PI) * r;
	float
	  dot_y = sin (a * 2 * M_PI) * r;
	canvas->SetPixel (center_x + dot_x, center_y + dot_y, 255, 0, 0);
	usleep (1 * 100);	// wait a little to slow down things. 
      }*/
    while (isThreadRunning()){
      continue;   
    }
    canvas->Clear();
    delete canvas;
  }
public:
void
  setPixel (int x, int y, int r, int g, int b)
  {
    canvas->SetPixel (x, y, r, g, b);
  }
  void fill(int r, int g, int b){canvas->Fill(r,g,b);}
  void clear(){canvas->Clear();}
};
