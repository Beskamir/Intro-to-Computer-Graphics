//
// This will store camera data within the scene
// Camera class based on:
//          https://www.youtube.com/watch?v=LRN_ewuN_k4
//          https://github.com/Hillsoft/Raytracer-Tutorial
//

#ifndef ASSIGNMENT4_CAMERA_H
#define ASSIGNMENT4_CAMERA_H

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
#include "../Raytracer/Ray.h"

using namespace std;
using namespace glm;

class Camera {
private:
    vec3 cameraOrigin;
    vec3 cameraForward;
    vec3 cameraUp;
    vec3 cameraRight;

    vec2 cameraSize;

    float scalar;
    float cameraAspectRatio;

public:
    Camera(vec3 cameraOrigin, vec3 target, vec3 upguide, float fov, float aspectRatio);

    ~Camera() = default;

    Ray generateRay(vec2 point);

};


#endif //ASSIGNMENT4_CAMERA_H
