//
// Math helper function created to do mathy stuff
//

#ifndef ASSIGNMENT4_MATH_H
#define ASSIGNMENT4_MATH_H

//Include GLM for all the vector stuffs.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

constexpr float kEpsilon = 1e-8;

//Get the square of a number
inline float square(float value){
    return value*value;
}

//Get the squared length of a vector
inline float lengthSquared(vec3 vector){
    return square(vector.x) + square(vector.y) + square(vector.z);
}

//Function based on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
inline bool solveQuadratic(float &a, float &b, float &c, float &t0, float &t1){
    float discriminant = (b*b) - (4 * a * c);
    if (discriminant < 0.0f){
        return false; //can't find real solution
    }
    // Find two points of intersection
    t0 = (-b - sqrt(discriminant)) / (2 * a);
    t1 = (-b + sqrt(discriminant)) / (2 * a);
    //printf("potentialHit");
    return true; //found a real solution
}

inline float clampMyMath(float lowerBound, float upperBound, float value) {
    return std::max(lowerBound, std::min(upperBound, value));
}

inline vec3 getNewRayOrigin(float isOutside, vec3 &hitPoint, vec3 biasValue) {
    //if (isOutside) {
    //    return (glm::dot(rayDirection, normal) < 0) ?
    //           hitPoint + normal * biasValue :
    //           hitPoint - normal * biasValue;
    //} else {
    if(isOutside){
        return hitPoint - biasValue;
    }
    else{
        return hitPoint + biasValue;
    }
}

#endif //ASSIGNMENT4_MATH_H
