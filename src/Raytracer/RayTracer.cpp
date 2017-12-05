//
// This will run the ray tracing algorithm
//

#include "RayTracer.h"
//#include "../Scene/Shading/Color.h"
//#include "ImageData.h"
//#include "Ray.h"
//#include "../Scene/Shading/Lights.h"

RayTracer::RayTracer(int samples, int width, int height) {
    this->samples = samples;
    this->width = width;
    this->height = height;
}

void RayTracer::cpuRender(ImageData *image, Camera camera, Scene scene) {

    vector<Sphere> modelSpheres = scene.getSpheres();
    vector<Mesh> modelMeshes = scene.getMeshes();
    Lights lights;// = scene.getLights();
    ModelSet modelSet;
    for (int i = 0; i < modelSpheres.size(); ++i) {
        modelSet.addModel(&modelSpheres[i]);
    }
    for (int j = 0; j < modelMeshes.size(); ++j) {
        modelSet.addModel(&modelMeshes[j]);
    }

    //modelObjects[0].
    vec3 distance;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            //Color pixel = superSample(x,y,modelSet,camera);
            Color pixel(0);

            //vec2 screenCoord((((2.0f * (x)) / (float)width) - 1.0f),
            //                 (1.0f - ((2.0f * (y)) / (float)height)));
            ////pixel = castRay(ray);
            //Ray ray = camera.generateRay(screenCoord);
            //
            //Intersection intersection(ray);
            //if(modelSet.intersect(intersection)){
            //    pixel = intersection.getColor();
            //}
            pixel = superSample(x,y,modelSet,camera,lights);
            //for (int i = 0; i < modelSpheres.size(); ++i) {
            //    if(modelSpheres[i].intersect(intersection)){
            //        pixel = intersection.getColor();
            //    }
            //}


            //if(){
            //    pixel =
            //}
            //distance = scene.getSphereCollisions(ray);

            image->storePixel(x, y, pixel);
        }
    }
}



// following function thanks to what was provided alongside the assignment.
// This function generates point on the image plane and starts a trace through them.
// Grid supersampling is also implemented.
Color RayTracer::superSample(int x, int y, ModelSet modelSet,Camera camera,Lights lights){
    vec2 windowCoord;
    Color color = Color(0.0,0.0,0.0,0.0);
    for(int i = 0; i < samples; i++){
        for(int j = 0; j < samples; j++){
            windowCoord.x = (float) x + (float)i/(float)samples;
            windowCoord.y = (float) y + (float)i/(float)samples;
            vec2 screenCoord((((2.0f * (windowCoord.x)) / (float)width) - 1.0f),
                             (1.0f - ((2.0f * (windowCoord.y)) / (float)height)));

            Ray ray = camera.generateRay(screenCoord);
            color = color + castRay(ray, modelSet, lights, 0);

            //Ray r = scene->makeRay(one,two);
            //c = c+trace(r,0);
        }
    }
    color = color*(1.0/float(samples*samples));
    return color;
}

Color RayTracer::castRay(Ray ray, ModelSet modelSet, Lights lights, int depth){
    Color hitColor(0);
    //Color base(1);
    Intersection intersection(ray);
    if(modelSet.intersect(intersection)){
        hitColor = intersection.getColor();
    }
    return hitColor;
}

void RayTracer::gpuRender(Scene scene,Camera camera) {

}
