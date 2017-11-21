//
// Created by Sebastian on 11/13/2017.
//

#ifndef ASSIGNMENT2_OPENGL_PROGRAM_H
#define ASSIGNMENT2_OPENGL_PROGRAM_H
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

#include "ShaderProgram.h"
//#include "vertexArray.h"
#include "Model.h"
#include "Camera.h"
#include "Mouse.h"
#include "Transformations.h"

class OpenGL_Program {

private:
    //shaders
    ShaderProgram mShaders;
    //Window related stuff, (pointer to and dimensions)
    GLFWwindow *window;
    int *window_width, *window_height;

    Camera camera;
    Mouse mouse;
    Transformations transformations;

    //Vector array of models within the scene
    vector<Model> modelObjects;

    struct Modes{
        bool fps;
        bool scale;
        bool rotate;
        bool move;
    };
    Modes modes = {false,false,false,false};

    // Axis which to rotate a given object around
    struct UseAxis{
        bool x;
        bool y;
        bool z;
    };
    UseAxis useAxis = {false, false, false};

    bool activeKeys[1024]={false};


    void renderToScreen(vector<Model> modelObjects);

public:

    ~OpenGL_Program()= default;
    OpenGL_Program()= default;
    void mainRender();
    void init_Program(GLFWwindow *window, int *window_width, int *window_height);
    void handleKeyCallback(int key, int action);

    void handleKeyPress(int key);

    void handleScrollCallback(double yoffset);

    void moveCameraWASD(double deltaTime);

    void handleMouseMovement(double xpos, double ypos);

    void finalizeTransformation();
};


#endif //ASSIGNMENT2_OPENGL_PROGRAM_H
