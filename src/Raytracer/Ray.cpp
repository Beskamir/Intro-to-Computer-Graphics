//
// Ray class
//

#include "Ray.h"

Ray::Ray(const vec3 rayOrigin, const vec3 direction, float rayTImeValueMax) {
    this->rayOrigin=rayOrigin;
    this->direction=direction;
    this->rayTimeValueMax=rayTImeValueMax;
}

vec3 Ray::calculate(float t) {
    return rayOrigin + (direction * t);
}

void Ray::moveRay(vec3 pos) {
    rayOrigin -= pos;
}

vec3 Ray::getOrigin(){
    return rayOrigin;
}

vec3 Ray::getDirection(){
    return direction;
}

float Ray::getTimeValueMax() {
    return rayTimeValueMax;
}

//Ray::Ray(Ray &rayOld) {
//    rayOrigin = rayOld.getOrigin();
//    direction = rayOld.getDirection();
//    rayTimeValueMax = rayOld.getTimeValueMax();
//}
