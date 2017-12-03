//
// Boilerplate based on:
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
#include "OpenGL_Program.h"


using namespace std;

int mainOpenGL(int argc, char *argv[]);
bool setupOpenGL(GLFWwindow **window);
void setupWindowCallbacks(GLFWwindow **window);

//vec2 getMouseLocation();
//void teleportMouse(double xpos, double ypos);
//double getMouseDistance(vec2 mousePosition);

//Handle inputs
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

#endif //ASSIGNMENT2_MAIN_H
