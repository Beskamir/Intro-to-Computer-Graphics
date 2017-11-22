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
        mat4 modelTransformation;
        vector<Texture> textures;
    };
    struct Bound{
        float xCoord[2];
        float yCoord[2];
        float zCoord[2];
    };

    mat4 tempTransform;
    mat4 appliedTransforms;

    void openOBJ(string filepath);
    void moveToOrigin();
    void computeMiddle();
    void updateBoundingBox(vec3 vertex);
    void setupBuffers();

    //struct Transformations{
    //    mat4 scaleMat;
    //    mat4 rotateMat;
    //    mat4 transformMat;
    //};
    //Transformations transformations;
    //vec3 scaleMat=vec3(1.0f,1.0f,1.0f);
    //mat4 scaleMat;
    vec3 tempScaleVec=vec3(1.0f,1.0f,1.0f);
public:
    MeshData meshData;
    Bound boundingBox;
    vec3 origin;

    //GLuint mTexture=0;
    //int imageWidth=0, imageHeight=0;

    Model();
    Model(string filepath);

    void scaleModel(vec3 scaleVec);
    void addTexture(string texturePath);
    GLuint openTexture(string filename);
    void drawModel(GLint modelLoc, GLint tInverseLoc, bool transforming, bool worldAxis);
    void finalizeModelingTransformation(bool worldAxis);

    //void scaleWithWindow(float scaleX, float scaleY);
    void setTempTransform(mat4 tempTransform);
};


#endif //ASSIGNMENT2_MODEL_H
