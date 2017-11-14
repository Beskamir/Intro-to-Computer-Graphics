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
#include "vertexArray.h"
#include "Model.h"

class OpenGL_Program {

private:
    ShaderProgram mShaders;
    ShaderProgram lineShader;
    GLFWwindow *window;


    void setupTransformations(ShaderProgram shaderProgram);
    void setTextureUsage(int textureUsage);
    void renderToScreen(vertexArray &verts);
    void drawImage(vertexArray &verts);

public:

    ~OpenGL_Program()= default;
    OpenGL_Program(GLFWwindow *window);
    void mainRender();

};


#endif //ASSIGNMENT2_OPENGL_PROGRAM_H
