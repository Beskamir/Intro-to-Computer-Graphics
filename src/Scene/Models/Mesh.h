//
// Mesh data class
//

#ifndef ASSIGNMENT4_MESH_H
#define ASSIGNMENT4_MESH_H

#include <iostream>
#include <vector>

using namespace std;

#include "../Model.h"
#include "../Shading/Material.h"

class Mesh: public Model {
public:
    struct Vertex {
        vec3 Position;
        vec3 Normal;
        vec2 uvCoords;
    };
    //vector<Vertex> verticies;
    struct MeshData{
        vector<Vertex> vertices;
    };
    MeshData meshData;
public:
    Mesh() = default;
    ~Mesh() = default;

    void addModel(string filepath);
    //void addTriangle(vec3 p1, vec3 p2, vec3 p3, vec3 normal);
    void addTriangle(vector<vec3> point,vec3 normal,vector<vec2> uv = {vec2(0),vec2(0),vec2(0)});

    void addTexture(char type, string texturePath);

    bool intersect(Ray &ray,float &tNearI,int &indexI,vec2 &uvI) override;

    void getSurfaceProperties(vec3 &hitPoint, Ray &ray, int &index, vec2 &uv, vec3 &normal, vec2 &stCoords) override;

    void openOBJ(string filename);

    bool
    rayTriangleIntersect(const vec3 &vert0, const vec3 &vert1, const vec3 &vert2, Ray &ray, float &tNearTemp, vec2 &uvTemp);
};


#endif //ASSIGNMENT4_MESH_H
