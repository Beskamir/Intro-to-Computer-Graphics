//
// Based on Assignment 1 boilerplate
//

#ifndef ASSIGNMENT2_VERTEXARRAY_H
#define ASSIGNMENT2_VERTEXARRAY_H

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

class vertexArray {
    std::map<string, GLuint> buffers;
    std::map<string, int> indices;
public:
    GLuint id;
    unsigned int count;

    vertexArray(int c);
    vertexArray(const vertexArray &v);

    void addBuffer(string name, int index, vector<float> buffer);
    void updateBuffer(string name, vector<float> buffer);

    ~vertexArray();
};


#endif //ASSIGNMENT2_VERTEXARRAY_H
