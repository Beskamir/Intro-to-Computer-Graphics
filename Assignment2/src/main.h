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

#include <GLFW/glfw3.h>

// Include shader class
#include "shader.h"
#include "vertexArray.h"

using namespace std;


const GLuint WINDOW_WIDTH = 1024, WINDOW_HEIGHT = 1024; // Window dimensions
GLFWwindow *window; // Create "global" glfw window

int main(int argc, char *argv[]);
void mainRender();
void renderToScreen(Shader mainShaders, VertexArray &verts);
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#endif //ASSIGNMENT2_MAIN_H
