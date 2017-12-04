//
// Ray class
//

#include "Ray.h"

Ray::Ray(const vec3 rayOrigin, const vec3 direction, float tMax) {
    this->rayOrigin=rayOrigin;
    this->direction=direction;
    this->tMax=tMax;
}

vec3 Ray::calculate(float t) {
    return rayOrigin + (direction * t);
}

