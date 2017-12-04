//
// Created by Sebastian on 04/12/2017.
//

#ifndef ASSIGNMENT4_MODELOBJECTS_H
#define ASSIGNMENT4_MODELOBJECTS_H


#include "../Model.h"
#include "Sphere.h"

class ModelSet: public Model {
private:
    vector<Model*> models;

public:
    ModelSet()= default;

    ~ModelSet() override = default;

    void addModel(Model* model);

    bool intersect(Intersection& intersection) override;

    bool doesIntersect(Ray& ray) override;
};


#endif //ASSIGNMENT4_MODELOBJECTS_H
