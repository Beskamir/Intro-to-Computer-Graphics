//
// Created by Sebastian on 12/4/2017.
//

#ifndef ASSIGNMENT4_MATERIAL_H
#define ASSIGNMENT4_MATERIAL_H


#include "MaterialTypes.h"

class Material {
private:
    MaterialType materialType;

public:
    Material();
    Material(MaterialType materialType);
    ~Material() = default;


    MaterialType getMaterialType();

};


#endif //ASSIGNMENT4_MATERIAL_H
