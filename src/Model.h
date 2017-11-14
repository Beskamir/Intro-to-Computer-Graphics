//
// Created by Sebastian on 11/13/2017.
//

#ifndef ASSIGNMENT2_MODEL_H
#define ASSIGNMENT2_MODEL_H
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
#include "vertexArray.h"

#include "Texture.h"


using namespace std;

class Model {
private:
    //typedef struct {
    //    float x;
    //    float y;
    //    float z;
    //    float w;
    //} Position;
    //typedef struct {
    //    float x;
    //    float y;
    //    float z;
    //} Normal;
    //typedef struct {
    //    float s;
    //    float t;
    //    float u;
    //} TexCoord;
    //typedef struct {
    //    Position pos;
    //    Normal norm;
    //    TexCoord tex;
    //} Vertex;
    //typedef struct {
    //    array<Vertex,3> vertex;
    //} Triangle;

    //struct Vert{
    //    float x,y,z;
    //};
    //struct Color{
    //    float r,g,b;
    //};
    //struct uvCoord{
    //    float u,v;
    //};

    struct MeshData{
        vector<vector<float>> vertices;
        vector<vector<float>> colors;
        vector<vector<float>> uvCoords;
    };

public:
    MeshData meshData;

    GLuint mTexture=0;
    int imageWidth=0, imageHeight=0;

    Model();
    Model(string filepath);

    void addTexture();

    void genImagePlane();

    vertexArray use();
};


#endif //ASSIGNMENT2_MODEL_H
