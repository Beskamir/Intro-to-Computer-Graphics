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
    float usableScreenSize = 0.9;

    vec2 mouseLastPosition={0,0};
    vec2 mouseLastPerpendicular={0,0};
    vec2 mouseCurrentPosition={0,0};
    //vec2 mouseGlobal={0,0};
    vec2 maxRegion={0.9f,0.9f};
    vec2 minRegion={-0.9f,-0.9f};
    mat2 counter = mat2({0,0},{0,0});

    vec2 getMouseLocation();
    vec2 getPerpendicular(vec2 mousePosition);

public:
    Mouse() = default;
    Mouse(GLFWwindow *window, int *window_width, int *window_height);
    ~Mouse() = default;

    void setMouseLast();
    vec2 getMouseLast();

    void setMouseCurrent();
    vec2 getMouseCurrent();

    vec2 getMouseDifference(vec2 mouseFinal, vec2 mouseInitial);

    void reset();

    void teleportMouse(double xpos, double ypose);
    int getPositivity(vec2 tvec21);
    double getDistance(vec2 mousePosition);

    vec2 getMouseScreenLoc();
};


#endif //ASSIGNMENT3_MOUSE_H
