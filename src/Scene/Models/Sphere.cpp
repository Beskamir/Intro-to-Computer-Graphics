//
// Sphere model class
//

#include "Sphere.h"

Sphere::Sphere(vec3 origin, float radius) {
    this->origin=origin;
    this->radius=radius;

}

void Sphere::changeSize(float scalar) {
    radius*=scalar;
}

void Sphere::move(vec3 deltaMovement) {
    origin+=deltaMovement;
}
