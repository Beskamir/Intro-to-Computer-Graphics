//
// Sphere model class
//

#include "Sphere.h"

Sphere::Sphere(vec3 origin, float radius, Color color) {
    this->center=origin;
    this->radius=radius;
    this->color=color;

}

void Sphere::changeSize(float scalar) {
    radius*=scalar;
}

void Sphere::move(vec3 deltaMovement) {
    center+=deltaMovement;
}

bool Sphere::intersect(Intersection &intersection) {
// Transform ray so we can consider origin-centred sphere
    Ray localRay = intersection.getRay();
    localRay.moveRay(center);
    //localRay.origin -= centre;

    // Calculate quadratic coefficients
    //float a = localRay.direction.length2();
    float a = lengthSquared(localRay.getDirection());
    float b = 2 * dot(localRay.getDirection(),localRay.getOrigin());
    float c = lengthSquared(localRay.getOrigin()) - square(radius);

    // Check whether we intersect
    float discriminant = (b*b) - 4 * a * c;

    if (discriminant < 0.0f)
    {
        return false;
    }

    // Find two points of intersection, t1 close and t2 far
    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);


    float tValue = intersection.getRayTimeValue();

    // First check if close intersection is valid
    if (t1 > RAY_T_MIN && t1 < tValue){
        intersection.setRayTimeValue(t1);
    }
    else if (t2 > RAY_T_MIN && t2 < tValue){
        intersection.setRayTimeValue(t2);
    }
    else{
        // Neither is valid
        return false;
    }

    // Finish populating intersection
    intersection.setModelPointer(this);
    intersection.setColor(color);

    return true;
}

bool Sphere::doesIntersect(Ray &ray) {
// Transform ray so we can consider origin-centred sphere
    Ray localRay = ray;
    localRay.moveRay(center);

    // Calculate quadratic coefficients
    float a = lengthSquared(localRay.getDirection());
    float b = 2 * dot(localRay.getDirection(), localRay.getOrigin());
    float c = lengthSquared(localRay.getOrigin()) - square(radius);

    // Check whether we intersect
    float discriminant = square(b) - 4 * a * c;

    if (discriminant < 0.0f)
    {
        return false;
    }

    float tValue = ray.getTimeValueMax();

    // Find two points of intersection, t1 close and t2 far
    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    if (t1 > RAY_T_MIN && t1 < tValue)
        return true;

    float t2 = (-b + sqrt(discriminant)) / (2 * a);
    if (t2 > RAY_T_MIN && t2 < tValue)
        return true;

    return false;
}
