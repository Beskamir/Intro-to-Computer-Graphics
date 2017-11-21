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
    // Axis which to rotate a given object around
    struct UseAxis{
        bool x;
        bool y;
        bool z;
    };

public:
    Transformations()= default;
    ~Transformations()= default;


    void scale(UseAxis useAxis, Mouse mouse);
    void rotate(UseAxis useAxis,Mouse mouse);
    void translate(UseAxis useAxis, Mouse mouse);
    mat4 getTransformation();
    void clear();


};


#endif //ASSIGNMENT2_TRANSFORMATIONS_H
