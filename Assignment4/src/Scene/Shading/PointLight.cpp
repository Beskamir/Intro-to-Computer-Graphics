//
// Created by Sebastian on 12/4/2017.
//

#include "PointLight.h"

PointLight::PointLight(vec3 position, vec3 color) {
    this->position = position;
    this->color = color;
}

vec3 PointLight::getDirection(vec3 destination) {
    return (position - destination);
}

vec3 PointLight::getColor() {
    return color;
}
