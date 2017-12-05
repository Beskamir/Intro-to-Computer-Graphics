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

    bool intersect(Intersection& intersection) override;
    bool doesIntersect(Ray& ray) override;
};


#endif //ASSIGNMENT4_MESH_H
