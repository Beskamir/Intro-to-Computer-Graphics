//
// Created by Sebastian on 11/20/2017.
//

#ifndef ASSIGNMENT2_TRANSFORMATIONS_H
#define ASSIGNMENT2_TRANSFORMATIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

//Modified to do it for both Windows and non-windows.
#ifdef _WIN32
#include <GL/glew.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#endif
//Include glfw
#include <GLFW/glfw3.h>

//Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mouse.h"
using namespace std;
using namespace glm;

class Transformations {
private:
    mat4 transformation;
    vec3 mouseBasedTranslation;

public:
    Transformations()= default;
    ~Transformations()= default;


    void scale(bvec3 useAxis, Mouse mouse);
    void rotate(bvec3 useAxis,Mouse mouse);
    void translate(bvec3 useAxis, vec3 selectedObject, vec3 projectedMousePos);
    mat4 getTransformation();
    void clear();


    void scale(bvec3 useAxis, float scaleFactor);

    void rotate(bvec3 useAxis, float angle);

    void translate(bvec3 useAxis, vec3 move);
};


#endif //ASSIGNMENT2_TRANSFORMATIONS_H
