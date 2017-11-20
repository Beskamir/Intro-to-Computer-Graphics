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

#include "ShaderProgram.h"
//#include "vertexArray.h"
#include "Model.h"

class OpenGL_Program {

private:
    ShaderProgram mShaders;
    //ShaderProgram lineShader;
    GLFWwindow *window;
    int *window_width, *window_height;

    void renderToScreen(vector<Model> modelObjects);
    //void setTextureUsage(int textureUsage);
    void setupTransformations(ShaderProgram shaderProgram, int i);
    void drawModel(Model model);

    // Camera
    vec3 cameraPosition = vec3(0.0f, 0.0f, 0.0f);
    vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
    vec3 cameraUp = vec3(0.0f, 1.0f,  0.0f);
    float cameraSpeed = 0.05f;
    GLfloat yaw   = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
    GLfloat pitch =   0.0f;
    vector<Model> modelObjects;

public:

    ~OpenGL_Program()= default;
    OpenGL_Program()= default;
    void mainRender();
    void init_Program(GLFWwindow *window, int *pInt, int *pInt1);
    void moveCamera(bool forward, bool backward, bool right, bool left);

    void changeCameraSpeed(float changeSpeed);

    void initalCameraLocation(Model model);

    void rotateView(float xOffset, float yOffset);

    void centerView(int scaleX, int scaleY);

    //void scaleWithWindow(float scaleX, float scaleY);
    void scaleModel(vec3 scaleVec);
};


#endif //ASSIGNMENT2_OPENGL_PROGRAM_H
