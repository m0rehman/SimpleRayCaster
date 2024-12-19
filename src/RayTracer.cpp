#include "RayTracer.h"

RayTracer::RayTracer(int w, int h) {
    width = w;
    height = h;
    renderResult.allocate(width, height, OF_IMAGE_COLOR);
    
    // Default light positions
    lightPos1 = ofVec3f(2, 3, -3);
    lightPos2 = ofVec3f(-3, 2, -3);
}

void RayTracer::setLightPositions(ofVec3f pos1, ofVec3f pos2) {
    lightPos1 = pos1;
    lightPos2 = pos2;
}

void RayTracer::addSphere(Sphere s) {
    spheres.push_back(s);
}

bool RayTracer::isInShadow(ofVec3f hitPoint, ofVec3f L, float distanceToLight) {
    // Move start point slightly away from surface to avoid self-intersection
    ofVec3f shadowRayOrigin = hitPoint + L * 0.001f;
    
    // Check each sphere to see if it blocks the light
    for (int i = 0; i < spheres.size(); i++) {
        float t;
        if (spheres[i].intersect(shadowRayOrigin, L, t)) {
            if (t < distanceToLight) return true;
        }
    }
    return false;
}

void RayTracer::render() {
    // Background gradient colors
    ofColor topColor(60, 88, 255);      // Sky blue
    ofColor bottomColor(234, 230, 100); // Light yellow

    // Loop through every pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Convert pixel coordinates to -1 to 1 range
            float u = (2.0f * x / width) - 1.0f;
            float v = 1.0f - (2.0f * y / height);
            
            // Create ray from camera (0,0,0) through pixel
            ofVec3f rayOrigin(0, 0, 0);
            ofVec3f rayDir(u, v, -1);
            rayDir.normalize();
            
            // Find closest sphere that ray hits
            float closest_t = INFINITY;
            Sphere* hit_sphere = NULL;
            
            for (int i = 0; i < spheres.size(); i++) {
                float t;
                if (spheres[i].intersect(rayOrigin, rayDir, t)) {
                    if (t < closest_t) {
                        closest_t = t;
                        hit_sphere = &spheres[i];
                    }
                }
            }
            
            // Color the pixel
            ofColor pixelColor;
            
            // If we hit a sphere, do lighting calculation
            if (hit_sphere != NULL) {
                ofVec3f hitPoint = rayOrigin + rayDir * closest_t;
                ofVec3f N = (hitPoint - hit_sphere->center).normalize();
                ofVec3f V = -rayDir;
                
                // ambient lighting
                float ambient = hit_sphere->ka;
                float totalDiffuse = 0;
                float totalSpecular = 0;
                
                // Add contribution from first light
                ofVec3f L1 = (lightPos1 - hitPoint);
                float dist1 = L1.length();
                L1.normalize();
                
                if (!isInShadow(hitPoint, L1, dist1)) {
                    // Calculate shadow vector
                    ofVec3f R1 = (2.0f * N.dot(L1) * N - L1).normalize();
                    
                    // Add diffuse and specular for light 1
                    totalDiffuse += hit_sphere->kd * max(0.0f, N.dot(L1));
                    totalSpecular += hit_sphere->ks * pow(max(0.0f, V.dot(R1)), hit_sphere->shininess);
                }
                
                // Add contribution from second light
                ofVec3f L2 = (lightPos2 - hitPoint);
                float dist2 = L2.length();
                L2.normalize();
                
                if (!isInShadow(hitPoint, L2, dist2)) {
                    ofVec3f R2 = (2.0f * N.dot(L2) * N - L2).normalize();
                    totalDiffuse += hit_sphere->kd * max(0.0f, N.dot(L2));
                    totalSpecular += hit_sphere->ks * pow(max(0.0f, V.dot(R2)), hit_sphere->shininess);
                }
                
                // Average the contributions from both lights
                totalDiffuse *= 0.5f;
                totalSpecular *= 0.5f;
                
                // Calculate final color with all lighting terms
                float specularIntensity = min(1.0f, totalSpecular);
                pixelColor.r = min(255.0f, hit_sphere->color.r * (ambient + totalDiffuse) + 255 * specularIntensity);
                pixelColor.g = min(255.0f, hit_sphere->color.g * (ambient + totalDiffuse) + 255 * specularIntensity);
                pixelColor.b = min(255.0f, hit_sphere->color.b * (ambient + totalDiffuse) + 255 * specularIntensity);
            }
            // use background color
            else {
                float t = (rayDir.y + 1.0f) * 0.5f;
                pixelColor = bottomColor.getLerped(topColor, t);
            }
            
            renderResult.setColor(x, y, pixelColor);
        }
    }
    renderResult.update();
}

void RayTracer::draw() {
    renderResult.draw(0, 0);
}
