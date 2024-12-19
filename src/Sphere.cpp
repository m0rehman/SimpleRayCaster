#include "Sphere.h"

Sphere::Sphere(ofVec3f c, float r, ofColor col,
               float ambient, float diffuse, float specular, float n) {
    center = c;
    radius = r;
    color = col;
    ka = ambient;
    kd = diffuse;
    ks = specular;
    shininess = n;
}

// Ray-sphere intersection test
bool Sphere::intersect(ofVec3f rayOrigin, ofVec3f rayDir, float &t) {
    // Get vector from ray origin to sphere center
    ofVec3f oc = rayOrigin - center;
    
    // Calculate quadratic equation values
    // at² + bt + c = 0
    float a = rayDir.dot(rayDir);             // a = d.d
    float b = 2.0f * oc.dot(rayDir);          // b = 2(oc.d)
    float c = oc.dot(oc) - radius * radius;    // c = oc.oc - rr^2
    
    // b^2 - 4ac
    float discriminant = b*b - 4*a*c;
    
    // If discriminant is negative, ray misses sphere
    if (discriminant < 0) {
        return false;
    }
    
    // Find closest intersection point using quadratic formula
    float t0 = (-b - sqrt(discriminant)) / (2.0f * a);
    float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
    
    t = (t0 < t1) ? t0 : t1;
    return t > 0;
}
