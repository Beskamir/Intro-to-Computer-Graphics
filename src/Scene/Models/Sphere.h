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

using namespace std;
using namespace glm;

class Sphere{
private:
    vec3 origin={0,0,0};
    float radius = 1.0f;

public:
    Sphere() = default;
    Sphere(vec3 origin,float radius);
    ~Sphere() = default;




    void move(vec3 deltaMovement);
    void changeSize(float scalar);


};


#endif //ASSIGNMENT4_SPHERE_H
