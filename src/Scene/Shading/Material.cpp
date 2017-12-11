//
// Created by Sebastian on 12/4/2017.
//


#include "Material.h"
//#include "../../myMath.h"

Material::Material() {
    reset();
}

void Material::setIOR(float value) {
    ior = value;
}

//Function heavily based on:
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
vec3 Material::evalDiffuseColor(vec2 &stCoords) {
    if(texture){
        float scale = 5;
        vec2 st = vec2(0);

        float pattern = (fmodf(stCoords.x * scale, 1) > 0.5) ^ (fmodf(stCoords.y * scale, 1) > 0.5);

        return vec3(0.815, 0.235, 0.031) * (1 - pattern) + vec3(0.937, 0.937, 0.231) * pattern;

    }else{
        return diffuseColor;
    }
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

void Material::setKR(float value) {
    kr = value;
}

void Material::setSpecularExponet(float value) {
    specularExponent = value;
}

void Material::setMaterialType(MaterialType type) {
    this->type = type;
}

void Material::reset() {
    type = PHONG;
    specularColor = vec3(0.8);
    specularExponent = 32;
    diffuseColor = vec3(0.8);
    ambientColor = vec3(0);
    ior = 1.45;
    kr = -1;
    texture = false;
}

