//
// Created by Sebastian on 12/4/2017.
//

#include "Material.h"

Material::Material() {
    type = DIFFUSE_AND_GLOSSY;
    specularColor = vec3(0.8);
    specularExponent = 32;
    diffuseColor = vec3(0.8);
    indexOfRefraction = 1.45;
}

vec3 Material::evalDiffuseColor(vec2 &stCoords) {
    return diffuseColor;
}

void Material::setDiffuseColor(vec3 color) {
    diffuseColor = color;
}

void Material::setSpecularColor(vec3 color) {
    specularColor = color;
}

void Material::setIndexOfRefraction(float value) {
    indexOfRefraction = value;
}

void Material::setSpecularExponet(float value) {
    specularExponent = value;
}

void Material::setMaterialType(MaterialType type) {
    this->type = type;
}

