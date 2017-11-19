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

public:

    ~OpenGL_Program()= default;
    OpenGL_Program()= default;
    void mainRender();
    void init_Program(GLFWwindow *window, int *pInt, int *pInt1);
};


#endif //ASSIGNMENT2_OPENGL_PROGRAM_H
