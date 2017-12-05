//
// This will run the ray tracing algorithm
//

#ifndef ASSIGNMENT4_RAYTRACER_H
#define ASSIGNMENT4_RAYTRACER_H


#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "ImageData.h"
#include "../Scene/Shading/Lights.h"

class RayTracer {
private:
    int samples;
    int width,height;

public:
    RayTracer() = default;
    RayTracer(int samples,int width,int height);


    void cpuRender(ImageData *image, Camera camera, Scene scene);
    void gpuRender(Scene scene,Camera camera);

    Color castRay(Ray ray, ModelSet modelSet, Lights lights, int depth);

    //Color superSample(int x, int y);

    Color superSample(int x, int y, ModelSet modelSet, Camera camera,Lights lights);
};


#endif //ASSIGNMENT4_RAYTRACER_H
