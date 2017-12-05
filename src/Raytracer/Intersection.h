//
// Created by Sebastian on 04/12/2017.
//

#ifndef ASSIGNMENT4_INTERSECTION_H
#define ASSIGNMENT4_INTERSECTION_H


#include "../Scene/Shading/Color.h"
#include "Ray.h"
class Model;

class Intersection {
private:
    Ray ray;
    float rayTimeValue;
    Model *pModel;
    Color color;

public:
    Intersection() = default;
    Intersection(Ray &ray);
    ~Intersection() = default;

    bool intersected();
    vec3 position();

    void setRayTimeValue(float newRayTimeValue);
    void setModelPointer(Model *pointer);
    void setColor(Color color);

    Ray getRay();
    float getRayTimeValue();
    Color getColor();
};


#endif //ASSIGNMENT4_INTERSECTION_H
