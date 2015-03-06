#ifndef PARTICLE_H
#define PARTICLE_H
#include "ofTypes.h"
enum ForceType {CHARGE, SPRING, DIRECT};
class Particle
{
    public:
        ForceType forceType;
        //anchor used for spring and suck
        ofVec2f pos, vel, anchor, anchor_e, anchor_eacc;

        float mass;
        ofVec2f force;
        float charge;
        float damping;
        ofColor color;
        bool wrapCoordinates;
        Particle(float x = 0 , float y = 0, float m = .001, float c = 1, float d = 1, ofVec2f target = ofVec2f(0,0));
       // Particle(float x, float y);
      //  Particle();
        void update();
        void setForce(float x, float y){ force.set(x,y);}
        void setForce(ofVec2f f){ force = f;}
        void setCharge(float c){charge = c;}
        void setDamping(float d){damping = d;}
        void setMass(float m){mass = m;}
        void setVel(float x, float y){vel.set(x,y);}
        void setVel(ofVec2f v){vel = v;}
        ofVec2f getForce(){return force;}
        void target(ofVec2f t){anchor = t; setVel(0,0);}
        void setPos(float x, float y){pos.set(x,y);}
        virtual ~Particle();
    protected:
    private:
};

#endif // PARTICLE_H
