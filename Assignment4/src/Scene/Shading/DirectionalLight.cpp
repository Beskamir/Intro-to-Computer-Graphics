//
// Created by Sebastian on 05/12/2017.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 direction, vec3 color) {
    this->direction = (direction);
    this->color = color;
}

vec3 DirectionalLight::getDirection(vec3 destination) {
    return (direction);
}

vec3 DirectionalLight::getColor() {
    return color;
}
