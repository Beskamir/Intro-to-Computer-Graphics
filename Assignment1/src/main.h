//
// Main header file with all the definitions and needed includes
//

#ifndef ASSIGNMENT1_MAIN_H
#define ASSIGNMENT1_MAIN_H

#include <cmath>

#include "boilerplate.h"
#include "transformations.h"

int window_width = 1024;
int window_height = 1024;
float lineSize = 0.0025;
int targetDetail = 1;
//capping it at 10 since anything more barely has an effect
// even on a 2160p display and takes too long to compute
int maxDetail = 10;
GLenum drawingMode = GL_TRIANGLES;
bool drawTriangles=true;
bool recalculate = false;

int main(int argc, char *argv[]);
void loopRender(GLFWwindow *window);
void render(Program &program, VertexArray &va);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void window_size_callback(GLFWwindow* window, int width, int height);
vector<float> getVertsOnly(vector<vector<float>> vertData2D);
vector<float> getColorsOnly(vector<vector<float>> matrixData);

#endif //ASSIGNMENT1_MAIN_H
