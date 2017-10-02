//
// Created by Sebastian on 9/28/2017.
//

#ifndef ASSIGNMENT1_MAIN_H
#define ASSIGNMENT1_MAIN_H

#include "boilerplate.h"
#include "transformations.h"

int window_width = 1024;
int window_height = 1024;
int lineSize = 4;
GLenum drawingMode = GL_TRIANGLE_STRIP;

int main(int argc, char *argv[]);
void loopRender(GLFWwindow *window);
void render(Program &program, VertexArray &va);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void window_size_callback(GLFWwindow* window, int width, int height);
//void window_focus_callback(GLFWwindow* window, int focused);

#endif //ASSIGNMENT1_MAIN_H
