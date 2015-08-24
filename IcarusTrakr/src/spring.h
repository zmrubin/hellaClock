#ifndef SPRING_H
#define SPRING_H

#include "particle.h"
class Spring
{
    public:
        Particle * p1;
        Particle * p2;
        float k;
        float d;
        Spring();
        float getForce();
        virtual ~Spring();
    protected:
    private:
};

#endif // SPRING_H
