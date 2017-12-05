//
// Mesh data class
//

#include "Mesh.h"

void Mesh::addModel(string filepath) {

}

void Mesh::addTexture(char type, string texturePath) {

}

void Mesh::addTriangle(vec3 p1, vec3 p2, vec3 p3, vec3 normal) {

}

bool Mesh::intersect(Ray &ray, float &tNearI, int &indexI, vec2 &uvI) {
    return false;
}

void Mesh::getSurfaceProperties(vec3 &hitPoint, Ray &ray, int &index, vec2 &uv, vec3 &normal, vec2 &stCoords) {

}
