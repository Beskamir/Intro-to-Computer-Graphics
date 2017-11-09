//
// Shader class based on: https://learnopengl.com/code_viewer.php?type=header&code=shader
//

#ifndef SHADER_H
#define SHADER_H

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

#include <GLFW/glfw3.h>

using namespace std;

class Shader
{
public:
    GLuint Program;
    // Constructor generates the shader on the fly
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* tessCtrlPath, const GLchar* tessEvalPath,const GLchar* geometryPath);
    // Uses the current shader
    void Use(){
        glUseProgram(this->Program);
    }
};

#endif

