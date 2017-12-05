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
    Mesh() = default;
    ~Mesh() = default;

    void addModel(string filepath);
    void addTriangle(vec3 p1, vec3 p2, vec3 p3, vec3 normal);
    void addTexture(char type, string texturePath);

    bool intersect(Ray &ray,float &tNearI,int &indexI,vec2 &uvI) override;

    void getSurfaceProperties(vec3 &hitPoint, Ray &ray, int &index, vec2 &uv, vec3 &normal, vec2 &stCoords) override;

};


#endif //ASSIGNMENT4_MESH_H
