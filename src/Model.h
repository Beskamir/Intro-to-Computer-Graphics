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

//Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Include boost
//#include <boost/tokenizer.hpp>
//#include <boost/filesystem.hpp>

#include "vertexArray.h"
//#include "ImageTexture.h"

//using namespace boost;
using namespace std;
using namespace glm;

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
    struct Vertex {
        vec3 Position;
        vec3 Normal;
        vec2 uvCoords;
    };
    struct Texture {
        GLuint id;
        string type;
    };
    struct MeshData{
        vector<Vertex> vertices;
        //vector<int> indices;
        vector<Texture> textures;
    };

    //struct MeshData{
    //    vector<vector<float>> vertices;
    //    vector<vector<float>> colors;
    //    vector<vector<float>> uvCoords;
    //};

public:

    MeshData meshData;

    //GLuint mTexture=0;
    //int imageWidth=0, imageHeight=0;

    Model();
    Model(string filepath);

    //void addTexture();

    //void genImagePlane();

    void drawModel();

    void addTexture(string texturePath);

    GLuint openTexture(string filename);

    void openOBJ(string filepath);
};


#endif //ASSIGNMENT2_MODEL_H
