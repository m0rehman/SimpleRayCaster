#pragma once
#include "ofMain.h"
#include "RayTracer.h"

class ofApp : public ofBaseApp {
public:
    RayTracer* rayTracer;
    
    void setup();
    void draw();
    
    ofApp() {
        rayTracer = NULL;
    }
    
    ~ofApp() {
        delete rayTracer;
    }
};
