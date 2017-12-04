//
// Sphere model class
//

#ifndef ASSIGNMENT4_SPHERE_H
#define ASSIGNMENT4_SPHERE_H

//Include GLM for all the vector data.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "../Model.h"

using namespace std;
using namespace glm;

class Sphere:public Model{
private:
    vec3 center={0,0,0};
    float radius = 1.0f;
    Color color;

public:
    Sphere() = default;
    Sphere(vec3 center,float radius,Color color = Color(1));
    ~Sphere() override = default;


    void move(vec3 deltaMovement);
    void changeSize(float scalar);

    bool intersect(Intersection& intersection) override;
    bool doesIntersect(Ray& ray) override;

};


#endif //ASSIGNMENT4_SPHERE_H
