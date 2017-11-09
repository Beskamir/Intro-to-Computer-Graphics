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

//Include stb
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Include shader class
#include "shader.h"
#include "vertexArray.h"

using namespace std;

int window_width = 1024, window_height = 1024; // Window dimensions
GLFWwindow *window; // Create "global" glfw window

struct Mesh{
    vector<float> vertices;
    vector<float> colors;
    vector<float> texture;
};
struct PreRenderingMesh{
    vector<vector<float>> vertices;
    vector<vector<float>> colors;
    vector<vector<float>> texture;
};

struct Position{
    float x = 0;
    float y = 0;
};

float scaleFactor = 1.0f;
float scalingSpeed = 0.025f;
Position lastMousePos;
Position translate;

Mesh controlPoints;
vector<Mesh> splines;

GLuint imageStyle=0;
bool mouseDown = false;

int main(int argc, char *argv[]);

void loadImage(GLuint *mTexture, int *imageWidth, int *imageHeight);

void mainRender();
void renderToScreen(Shader mainShaders, vertexArray &verts);
void drawImage(vertexArray &verts);
void drawPoints();

void addControlPoint();
void setControlPoints(Shader mShader, int isControlPoint);

void setImageStyle(Shader shader);
void setupTransformations(Shader shader);
Mesh genImagePlane(int imageWidth,int imageHeight);
Position getMouseLocation();

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

#endif //ASSIGNMENT2_MAIN_H
