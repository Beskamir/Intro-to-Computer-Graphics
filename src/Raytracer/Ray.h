//
// Ray class
// based on: https://github.com/Hillsoft/Raytracer-Tutorial
//

#ifndef ASSIGNMENT4_RAY_H
#define ASSIGNMENT4_RAY_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

//Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../myMath.h"

using namespace std;
using namespace glm;

// In order to prevent bouncing rays self-intersecting
#define RAY_T_MIN 0.0001f

// 'Infinite' distance, used as a default value
#define RAY_T_MAX 1.0e30f

class Ray {
private:
    vec3 rayOrigin = vec3(0,0,0);
    vec3 direction;
    float rayTimeValueMax;

public:
    Ray() = default;

    //Ray(Ray &rayOld);
    Ray(vec3 rayOrigin, vec3 direction, float rayTImeValueMax = RAY_T_MAX);

    ~Ray()= default;

    vec3 calculate(float t);
    void moveRay(vec3 pos);

    float getTimeValueMax();
    vec3 getDirection();
    vec3 getOrigin();
};


#endif //ASSIGNMENT4_RAY_H
