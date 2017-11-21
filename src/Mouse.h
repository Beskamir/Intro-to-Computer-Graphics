//
// Created by Sebastian on 11/20/2017.
//

#ifndef ASSIGNMENT3_MOUSE_H
#define ASSIGNMENT3_MOUSE_H

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

using namespace std;
using namespace glm;

class Mouse {
private:
    GLFWwindow *window;
    int *window_width, *window_height;

    vec2 mouseLastPosition={0,0};
    vec2 mouseCurrentPosition={0,0};

    vec2 getMouseLocation();

public:
    Mouse() = default;
    Mouse(GLFWwindow *window, int *window_width, int *window_height);
    ~Mouse() = default;

    void setMouseLast();
    vec2 getMouseLast();

    void setMouseCurrent();
    vec2 getMouseCurrent();

    vec2 getMouseDifference();

};


#endif //ASSIGNMENT3_MOUSE_H
