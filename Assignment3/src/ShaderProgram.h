// ShaderProgram class based on TA's game of life with some help from Daniel Dastoor.
#ifndef ASSIGNMENT2_SP_H
#define ASSIGNMENT2_SP_H
//#include "OpenGL.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>


//Modified to do it for both Windows and non-windows.
#ifdef _WIN32
#include <GL/glew.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#endif
//Include glfw
#include <GLFW/glfw3.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
//using namespace glm;

class ShaderProgram{
public:
//private:
	GLuint id = 0;
//public:
	ShaderProgram();
	~ShaderProgram();
	bool attachShader(string fileName, GLenum type);
	bool link();
	bool use();
	static void unbind();
};

#endif //ASSIGNMENT2_SP_H
