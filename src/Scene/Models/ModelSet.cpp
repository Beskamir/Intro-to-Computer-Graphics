//
// Created by Sebastian on 04/12/2017.
//

#include "ModelSet.h"
#include "Sphere.h"

void ModelSet::addModel(Model* model) {
    models.push_back(model);
}

bool ModelSet::intersect(Intersection &intersection) {
    bool doesIntersect = false;
    for (auto &model : models) {
        if (model->intersect(intersection)){
            doesIntersect = true;
        }
    }
    return doesIntersect;
}

bool ModelSet::doesIntersect(Ray &ray) {
    for (auto &model : models) {
        if (model->doesIntersect(ray)) {
            return true;
        }
    }
    return false;
}
