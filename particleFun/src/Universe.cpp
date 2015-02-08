#include "Universe.h"

Universe::Universe()
{
    offScreenCharges.allocate(ofGetWidth(), ofGetHeight(),GL_RGB);
    offScreenCharges.begin();
    ofClear(0,0,0,0);
    offScreenCharges.end();
    verdana1.loadFont("verdana.ttf", ofGetWidth()*.155, true, true, true);//loadFont("verdana1.ttf", 70, true, true, true);
    verdana1.setLineHeight(34.0f);
    verdana1.setLetterSpacing(1.035);
}

void Universe::refString(string str)
{
    offScreenCharges.begin();
    ofClear(0,0,0,0);
    //ofPushMatrix();
    ofSetColor(255,255,255);
    ofRectangle bounds = verdana1.getStringBoundingBox(str, 0,0);
    verdana1.drawStringAsShapes(str, 0, ofGetHeight()/2+bounds.height/2);
    // ofPopMatrix();
    offScreenCharges.end();
    offScreenCharges.readToPixels(oscPix);
    float x = 0;
    float y = 0;
    vector<Particle*>::iterator it = particles.begin();
    for (float h = 0; h<ofGetHeight(); h++)
    {
        for (float w = 0; w<ofGetWidth()*3; w+=3)
        {
            if(oscPix[w+h*ofGetWidth()*3] == 255 )
            {
                (*it)->target(ofVec2f(x,y));//ofGetWidth()/2 , ofGetHeight()/2));
                //(*it)->pos = ofVec2f(x,y);
                (*it)->forceType = DIRECT;
                //  printf("%i \n", oscPix[w+h*ofGetWidth()*3]);
                it++;

            }
            else if (oscPix[w+h*ofGetWidth()*3] == 128)
            {
                continue; //reserved
            }
            x++;
        }
        x = 0;
        y ++;
    }
    while (it != particles.end()){
        (*it)->forceType = CHARGE;
        it++;
    }
    }


void Universe::update()
{
    vector<Particle*>::iterator it;

    for(it=particles.begin(); it != particles.end(); it++)
    {
        static float lastTime = 1;
        float dt = lastTime - ofGetElapsedTimef();
        lastTime = (float)ofGetElapsedTimef();


        if ((*it)->forceType == DIRECT)
        {
            float kp = 100;
            float ki =1;
            float kd = -10000;
            ofVec2f error_diff = (*it)->anchor_e - ((*it)->pos - (*it)->anchor);
            (*it)->anchor_e = (*it)->pos - (*it)->anchor;
            (*it)->anchor_eacc += (*it)->anchor_e;

            (*it)->force = - ( (*it)->anchor_e*kp + (*it)->anchor_eacc*ki + error_diff*kd ) ;
        }


            vector<Particle*>::iterator jt;

            for(jt=it; jt != particles.end(); jt++)
            {

                if(((*it)->forceType == CHARGE) || ((*jt)->forceType == CHARGE)){
                    ofVec2f unit = ((*jt)->pos - (*it)->pos).normalize();
                    ofVec2f f = unit * (*it)->charge * (*jt)->charge/((*it)->pos.distanceSquared((*jt)->pos));
                    (*it)->force -= f;
                    (*jt)->force +=f;
            }
            }


            (*it)->update();
        }


    }

    Universe::~Universe()
    {
        //dtor
    }
