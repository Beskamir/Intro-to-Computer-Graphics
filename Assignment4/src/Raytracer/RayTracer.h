//
// This will run the ray tracing algorithm
//

#ifndef ASSIGNMENT4_RAYTRACER_H
#define ASSIGNMENT4_RAYTRACER_H

//#include <bits/unique_ptr.h>

#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "ImageData.h"
#include "../Scene/Shading/Light.h"

class RayTracer {
private:
    int samples;
    int width,height;
    int maxDepth;
    vec3 backgroundColor;
    float biasValue = 1;
    Scene scene;
    bool threading;

public:
    RayTracer() = default;
    RayTracer(int samples,int width,int height,int maxDepth, Scene scene,bool threading);


    void cpuRender(ImageData *image, Camera camera);
    void gpuRender(Scene scene,Camera camera);

    vec3 castRay(Ray ray, vector<Model*> modelSet, vector<Light*> lights, int depth);

    //Color superSample(int x, int y);

    vec3 superSample(int x, int y, vector<Model*> modelSet, Camera camera,vector<Light*> lights);

    bool trace(Ray &ray, vector<Model*> &modelSet, float &tNear, int &index, vec2 &uv, Model **hitObject);

    vec3 computeDiffuse(Ray &ray, Model *hitObject, vec3 &tvec3, vec2 &stCoords, vec3 &normal, int &index, vector<Model *> modelSet, vector<Light*> &lights,vec2 uv);

    vec3 computeReflection(Ray &ray, Model *hitObject, vec3 &hitPoint, vec2 &stCoords, vec3 &normal, int &index,
                           vector<Model *> &modelSet, vector<Light *> &lights, vec2 &uv,int depth, bool isOutside);

    vec3 computeRefraction(Ray &ray, Model *hitObject, vec3 &hitPoint, vec2 &stCoords, vec3 &normal, int &index,
                               vector<Model *> &modelSet, vector<Light *> &lights, vec2 &uv, int depth, bool isOutside);

    float fresnel(Ray &ray, vec3 &normal, float &indexOfRefraction);

    vec3 refractRay(vec3 rayDirection, vec3 &normal, float &ior);
};


#endif //ASSIGNMENT4_RAYTRACER_H
