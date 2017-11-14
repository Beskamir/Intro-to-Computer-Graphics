//
// Boilerplate heavily based on:
// https://github.com/JoeyDeVries/LearnOpenGL
// https://learnopengl.com/code_viewer.php?code=getting-started/shaders-using-object
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
//Include glfw
#include <GLFW/glfw3.h>


// Include input handlers
#include "InputHandler.h"


using namespace std;

int window_width = 1024, window_height = 1024; // Window dimensions
GLFWwindow *window; // Create "global" glfw window

int main(int argc, char *argv[]);
bool setupOpenGL();
void setupWindowCallbacks();

#endif //ASSIGNMENT2_MAIN_H
