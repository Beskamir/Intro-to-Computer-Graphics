//
// Created by Sebastian on 12/4/2017.
//

#ifndef ASSIGNMENT4_POINTLIGHT_H
#define ASSIGNMENT4_POINTLIGHT_H


#include <glm/vec3.hpp>
#include "Light.h"

using namespace glm;
class PointLight: public Light {
public:
    vec3 position;
    vec3 color;
    //vec3 color;
public:
    PointLight(vec3 position, vec3 color);
    ~PointLight() override = default;
    vec3 getDirection(vec3 destination) override;
    vec3 getColor() override;
};


#endif //ASSIGNMENT4_POINTLIGHT_H
