#include "Ray.h"

Ray::Ray(ofVec3f o, ofVec3f d) {
    origin = o;
    direction = d.normalize();
}
