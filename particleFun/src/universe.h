#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "ofTypes.h"
#include "particle.h"
#include "ofMain.h"
class Universe
{
public:
    float normFactor;
    Universe();
    vector <Particle*> particles;
    ofPixels oscPix;
    void refString (string str);
    void update();
    virtual ~Universe();

protected:
private:

    ofTrueTypeFont	verdana1;
    ofFbo offScreenCharges;
};

#endif // UNIVERSE_H
