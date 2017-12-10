//
// Created by Sebastian on 12/4/2017.
//

#include "Material.h"

Material::Material() {
    type = PHONG;
    specularColor = vec3(0.8);
    specularExponent = 32;
    diffuseColor = vec3(0.8);
    indexOfRefraction = 1.45;
    ambientColor = vec3(0);
}

vec3 Material::evalDiffuseColor(vec2 &stCoords) {
    return diffuseColor;
}

void Material::setDiffuseColor(vec3 color) {
    diffuseColor = color;
    setAmbientColor();
}

void Material::setSpecularColor(vec3 color) {
    specularColor = color;
}

void Material::setAmbientColor(vec3 color) {
    ambientColor = color;
}

void Material::setAmbientColor(float factor) {
    ambientColor = factor * diffuseColor;
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

