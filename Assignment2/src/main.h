//
// Boilerplate heavily based on https://github.com/JoeyDeVries/LearnOpenGL
//

#ifndef ASSIGNMENT2_MAIN_H
#define ASSIGNMENT2_MAIN_H

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

// Include shader class
#include "Shader.h"

using namespace std;

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 1024;

int main();

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

#endif //ASSIGNMENT2_MAIN_H
