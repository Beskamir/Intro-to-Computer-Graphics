//
// Created by Sebastian on 04/12/2017.
//

#ifndef ASSIGNMENT4_MODEL_H
#define ASSIGNMENT4_MODEL_H


#include "../Raytracer/Intersection.h"

class Model {

public:
    virtual ~Model() = default;

    virtual bool intersect(Intersection &intersection) = 0;
    virtual bool doesIntersect(Ray &ray) = 0;

};


#endif //ASSIGNMENT4_MODEL_H
