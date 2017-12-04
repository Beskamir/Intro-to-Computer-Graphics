//
// Mesh data class
//

#ifndef ASSIGNMENT4_MESH_H
#define ASSIGNMENT4_MESH_H

#include <iostream>
#include <vector>

using namespace std;

#include "../Model.h"

class Mesh: public Model {

public:
    Mesh() = default;
    ~Mesh() = default;

    void addModel(string filepath);
    void addTexture(char type, string texturePath);

    bool intersect(Intersection& intersection) override;

    bool doesIntersect(Ray& ray) override;
};


#endif //ASSIGNMENT4_MESH_H
