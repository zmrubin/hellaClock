#include "particle.h"
#include "ofMain.h"

Particle::Particle(float x, float y, float m, float c, float d, ofVec2f target)
{   anchor = target;
    /*if (anchor.x == anchor.y == 0)
        forceType = CHARGE;
    else*/
        forceType = CHARGE;
    mass = m;
    charge = c;
    pos.set(x,y);
    vel.set(0,0);
    force.set(0,0);
    damping = d;
}

void Particle::update(){


    static float lastTime = 1;
    float dt = lastTime - ofGetElapsedTimef();
    float freqComp = 60/ofGetFrameRate();
    lastTime = (float)ofGetElapsedTimef();

    ofVec2f accel = force/mass;//force.getScaled(1/mass);
    //we are going about this the lazy way to save on some calculations


    //if (forceType == CHARGE) // and a 'wind resistance' term
        vel += accel*.01- vel*damping;

    pos += vel*.01 ;
   // printf("x%f y%y\n", vel.x, vel.y);

    if (pos.x > ofGetWidth())
        pos.x = 0;
    else if (pos.x < 0 - ofGetWidth() ){
        pos.x = ofGetWidth();
    }


    if (pos.y > ofGetHeight())
        pos.y = 0;
    else if (pos.y < 0 - ofGetHeight() ){
        pos.y = ofGetHeight();
    }
}
/*
Particle::Particle(float x, float y){
    pos.set(x,y);
    vel.set(0,0);
    charge = 1;
    mass = .001;
    force.set(0,0);
    damping = 1;
    }
Particle::Particle(){
    pos.set(0,0);
    vel.set(0,0);
    charge = 1;
    damping = 1;
    mass = .001;
    force.set(0,0);
    }*/
Particle::~Particle()
{
    //dtor
}
