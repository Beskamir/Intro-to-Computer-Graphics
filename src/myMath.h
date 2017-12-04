//
// Created by Sebastian on 04/12/2017.
//

#ifndef ASSIGNMENT4_MATH_H
#define ASSIGNMENT4_MATH_H

#include <glm/vec3.hpp>

using namespace glm;
inline float square(float value){
    return value*value;
}

inline float lengthSquared(vec3 vector){
    return square(vector.x) + square(vector.y) + square(vector.z);
}

#endif //ASSIGNMENT4_MATH_H
