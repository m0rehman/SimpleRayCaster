#include "ofApp.h"

void ofApp::setup() {
    // Create ray tracer at 1000x1000 resolution
    rayTracer = new RayTracer(1000, 1000);
    
    // Create our four spheres with different materials
    
    // metal sphere
    Sphere s1(ofVec3f(0, 1.2, -4),      // position
             0.7,                        // radius
             ofColor(220, 220, 220),     // silver color
             0.2,                        // low ambient
             0.3,                        // low diffuse
             1.0,                        // max specular
             256);                       // very sharp highlights
             
    // Matte red sphere
    Sphere s2(ofVec3f(-1, 0, -4),       // position
             0.7,                        // radius
             ofColor(255, 0, 0),         // red
             0.2,                        // moderate ambient
             0.9,                        // high diffuse
             0.0,                        // no specular
             1);
             
    // Semi-glossy blue sphere
    Sphere s3(ofVec3f(1, 0, -4),        // position
             0.7,                        // radius
             ofColor(0, 0, 255),         // blue
             0.2,                        // moderate ambient
             0.6,                        // medium diffuse
             0.4,                        // medium specular
             32);                        // moderate highlights
             
    // Plastic-like green sphere
    Sphere s4(ofVec3f(0, -1.2, -4),     // position
             0.7,                        // radius
             ofColor(0, 255, 0),         // green
             0.2,                        // moderate ambient
             0.7,                        // high diffuse
             0.3,                        // low-medium specular
             16);                        // soft highlights
    
    // Add all spheres to the scene
    rayTracer->addSphere(s1);
    rayTracer->addSphere(s2);
    rayTracer->addSphere(s3);
    rayTracer->addSphere(s4);
    
    // Set up two lights
    ofVec3f light1(3, 4, -2);     // Higher, from the right
    ofVec3f light2(-4, 1, -3);    // Lower, from the left
    rayTracer->setLightPositions(light1, light2);
    
    rayTracer->render();
}

void ofApp::draw() {
    rayTracer->draw();
}
