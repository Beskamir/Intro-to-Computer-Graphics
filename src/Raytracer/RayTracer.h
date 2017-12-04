//
// This will run the ray tracing algorithm
//

#ifndef ASSIGNMENT4_RAYTRACER_H
#define ASSIGNMENT4_RAYTRACER_H


#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "ImageData.h"

class RayTracer {

public:
    RayTracer() = default;


    void cpuRender(ImageData *image, Camera camera, Scene scene);
    void gpuRender(Scene scene,Camera camera);
};


#endif //ASSIGNMENT4_RAYTRACER_H
