//
// Created by Sebastian on 11/13/2017.
//

#ifndef ASSIGNMENT2_TEXTURE_H
#define ASSIGNMENT2_TEXTURE_H
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




using namespace std;

class Texture {

public:


    Texture()= default;
    ~Texture()= default;

    void addTexture(GLuint *mTexture, int *imageWidth, int *imageHeight);
};


#endif //ASSIGNMENT2_TEXTURE_H
