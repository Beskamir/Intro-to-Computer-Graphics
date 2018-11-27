//
// Created by Sebastian on 05/12/2017.
//

#ifndef ASSIGNMENT4_DIRECTIONALLIGHT_H
#define ASSIGNMENT4_DIRECTIONALLIGHT_H


#include "Light.h"

class DirectionalLight: public Light {
public:
    vec3 direction;
    vec3 color;
    //vec3 color;
public:
    DirectionalLight(vec3 direction, vec3 color);
    ~DirectionalLight() override = default;
    vec3 getDirection(vec3 destination) override;
    vec3 getColor() override;
};


#endif //ASSIGNMENT4_DIRECTIONALLIGHT_H
