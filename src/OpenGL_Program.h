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

    string keyboardNumericInput[3];

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
    bvec3 useAxis = {false, false, false};
    bvec3 axisSelected = {true,false,false};
    int currentAxisCounter = 0;
    int currentAxis = 0;
    bool worldAxis = false;

    vec3 transform;

    bool activeKeys[1024]={false};
    int selected = 0;

    void renderToScreen(vector<Model> modelObjects);
    void handleNonFPS_Mode(int key);
    void handleTransformationMode(int key);
    void moveCameraWASD(double deltaTime);
    void handleKeyPress(int key);

public:
    ~OpenGL_Program()= default;
    OpenGL_Program()= default;

    void init_Program(GLFWwindow *window, int *window_width, int *window_height);
    void commandLineArgs(vector<string> commandlineContents);
    void mainRender();

    void handleKeyCallback(int key, int action);
    void handleScrollCallback(double yoffset);

    void handleTextureModes(int key);
    void tryActivatingTransformations(int key);

    void handleMouseMovement(double xpos, double ypos);
    void endCurrentMode(); //is called by mouse click
    void parseConfigFile(string filepath);

    void tryUsingNumericKeyInput(int key);

    void keyboardTransformations();

    void getNumericKeyInput(int key);

    void fixStringErrors(string previous);

    void switchToOtherAxis();
};


#endif //ASSIGNMENT2_OPENGL_PROGRAM_H
