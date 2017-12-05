//
// Created by Sebastian on 12/4/2017.
//

#include "Material.h"

Material::Material(MaterialType materialType) {
    this->materialType = materialType;
}

MaterialType Material::getMaterialType() {
    return materialType;
}

Material::Material() {
    materialType = DIFFUSE_AND_GLOSSY;
}
