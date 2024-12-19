#pragma once
#include "ofMain.h"
#include "Sphere.h"

class RayTracer {
public:
    RayTracer(int w, int h);
    void render();
    void draw();
    void addSphere(Sphere s);
    void setLightPositions(ofVec3f pos1, ofVec3f pos2);
    bool isInShadow(ofVec3f hitPoint, ofVec3f lightDir, float distanceToLight);
    
    int width;
    int height;
    ofImage renderResult;
    vector<Sphere> spheres;
    
    // Two light positions
    ofVec3f lightPos1;
    ofVec3f lightPos2;
};
