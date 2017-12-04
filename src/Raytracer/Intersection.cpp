//
// Created by Sebastian on 04/12/2017.
//

#include "Intersection.h"

Intersection::Intersection(Ray &ray) {
    this->ray = ray;
    rayTimeValue = ray.getTimeValueMax();
    pModel = nullptr;
}

Ray Intersection::getRay() {
    return ray;
}

void Intersection::setModelPointer(Model *pointer) {
    pModel = pointer;
}

void Intersection::setColor(Color color) {
    this->color = color;
}

float Intersection::getRayTimeValue() {
    return rayTimeValue;
}

vec3 Intersection::position() {
    return ray.calculate(rayTimeValue);
}

bool Intersection::intersected() {
    return (pModel != nullptr);
}

void Intersection::setRayTimeValue(float newRayTimeValue) {
    rayTimeValue = newRayTimeValue;
}

Color Intersection::getColor() {
    return color;
}
