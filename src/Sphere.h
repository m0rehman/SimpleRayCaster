#pragma once
#include "ofMain.h"

class Sphere {
public:
    Sphere(ofVec3f c, float r, ofColor col,
           float ambient, float diffuse, float specular, float n);
    bool intersect(ofVec3f rayOrigin, ofVec3f rayDir, float &t);
    
    // Position and size
    ofVec3f center;
    float radius;
    
    ofColor color;
    float ka;  // ambient amount
    float kd;  // diffuse amount
    float ks;  // specular amount
    float shininess;
};
