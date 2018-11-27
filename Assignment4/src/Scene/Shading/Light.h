//
// Created by Sebastian on 12/4/2017.
//

#ifndef ASSIGNMENT4_LIGHTS_H
#define ASSIGNMENT4_LIGHTS_H


//Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
class Light {
public:
    Light() = default;
    virtual ~Light() = default;
    virtual vec3 getDirection(vec3 destination) = 0;
    virtual vec3 getColor() = 0;
};


#endif //ASSIGNMENT4_LIGHTS_H
