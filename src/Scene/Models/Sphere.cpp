//
// Sphere model class
//

#include "Sphere.h"

Sphere::Sphere(vec3 origin, float radius) {
    this->center=origin;
    this->radius=radius;
    //this->color=color;
}

void Sphere::changeSize(float scalar) {
    radius*=scalar;
}

void Sphere::move(vec3 deltaMovement) {
    center+=deltaMovement;
}

//Function based on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
bool Sphere::intersect(Ray &ray, float &tNear, int &index, vec2 &uv) {
    Ray localRay(ray.getOrigin(),ray.getDirection());
    localRay.moveRay(center);
    //float a = dot(localRay.getDirection(),localRay.getDirection());
    //float b = 2*dot(localRay.getDirection(),localRay.getOrigin());
    //float c = dot(localRay.getOrigin(),localRay.getOrigin() - square(radius));
    float a = lengthSquared(localRay.getDirection());
    float b = 2 * dot(localRay.getDirection(),localRay.getOrigin());
    float c = lengthSquared(localRay.getOrigin()) - square(radius);

    float t0, t1;
    if(!solveQuadratic(a, b, c, t0, t1)) return false;
    // First check if close intersection is valid
    if (t0 > RAY_T_MIN && t0 < tNear){
        tNear = t0;
    }
    else if (t1 > RAY_T_MIN && t1 < tNear){
        tNear = t1;
    }
    else{
        return false;
    }
    //cout<<"hit"<<endl;
    return true;
}

//Function based on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
void Sphere::getSurfaceProperties(vec3 &hitPoint, Ray &ray, int &index, vec2 &uv, vec3 &normal, vec2 &stCoords) {
    normal = normalize(hitPoint - center);
}
