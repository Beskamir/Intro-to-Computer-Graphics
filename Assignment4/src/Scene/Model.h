//
// Created by Sebastian on 04/12/2017.
//

#ifndef ASSIGNMENT4_MODEL_H
#define ASSIGNMENT4_MODEL_H


#include "Shading/Material.h"
#include "../Raytracer/Ray.h"

class Model {
private:
    //struct Material{
    //    MaterialType type = DIFFUSE_AND_GLOSSY;
    //    float diffuse = 0.5;
    //    float specular = 0.2;
    //    float specularExponent = 32;
    //    vec3 diffuseColor = vec3(1.0f,0.1f,0.1f);
    //};

public:
    Material material;

    virtual ~Model() = default;

    virtual bool intersect(Ray &ray,float &tNearI,int &indexI,vec2 &uvI) = 0;
    virtual void getSurfaceProperties(vec3 &hitPoint, Ray &ray, int &index, vec2 &uv, vec3 &normal, vec2 &stCoords)=0;
};


#endif //ASSIGNMENT4_MODEL_H
