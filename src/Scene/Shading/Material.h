//
// Created by Sebastian on 12/4/2017.
//

#ifndef ASSIGNMENT4_MATERIAL_H
#define ASSIGNMENT4_MATERIAL_H


#include "MaterialTypes.h"
#include <glm/vec3.hpp>

using namespace glm;

class Material {
public:
    MaterialType type;
    float specularExponent, indexOfRefraction;
    vec3 diffuseColor, specularColor, ambientColor;

    Material();
    ~Material() = default;

    void setDiffuseColor(vec3 color);
    void setSpecularColor(vec3 color);
    void setAmbientColor(vec3 color);
    void setAmbientColor(float factor = 0.05);
    void setIndexOfRefraction(float value);
    void setSpecularExponet(float value);
    void setMaterialType(MaterialType type);

    vec3 evalDiffuseColor(vec2 &stCoords);
};


#endif //ASSIGNMENT4_MATERIAL_H
