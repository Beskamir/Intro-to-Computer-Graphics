//
// This will run the ray tracing algorithm
//

#include "RayTracer.h"
//#include "../Scene/Shading/Color.h"
//#include "ImageData.h"
//#include "Ray.h"
//#include "../Scene/Shading/Light.h"

RayTracer::RayTracer(int samples, int width, int height, int maxDepth) {
    this->samples = samples;
    this->width = width;
    this->height = height;
    this->maxDepth = maxDepth;
}

void RayTracer::cpuRender(ImageData *image, Camera camera, Scene scene) {

    vector<Sphere> modelSpheres = scene.getSpheres();
    vector<Mesh> modelMeshes = scene.getMeshes();
    Light lights;// = scene.getLights();
    vector<Model*> modelSet;
    for (int i = 0; i < modelSpheres.size(); ++i) {
        modelSet.push_back(&modelSpheres[i]);
    }
    for (int j = 0; j < modelMeshes.size(); ++j) {
        //modelSet.push_back(modelMeshes[j]);
    }

    //modelObjects[0].
    vec3 distance;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            //Color pixel = superSample(x,y,modelSet,camera);
            vec3 pixel(0);

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
vec3 RayTracer::superSample(int x, int y, vector<Model*> modelSet,Camera camera,Light lights){
    vec2 windowCoord;
    vec3 color(0);
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
    color = color*(float)(1.0/float(samples*samples));
    return color;
}

//Function based heavily on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
vec3 RayTracer::castRay(Ray ray, vector<Model*> modelSet, Light lights, int depth){
    vec3 hitColor(0);
    if(depth > maxDepth){
        return hitColor;
    }
    float tNear = ray.getTimeValueMax();
    int index = 0;
    Model *hitObject = nullptr;
    vec2 uv;
    if(trace(ray,modelSet,tNear,index,uv,&hitObject)){
        vec3 hitPoint = ray.calculate(tNear);
        vec3 normal;
        vec2 stCoords;
        hitObject->getSurfaceProperties(hitPoint,ray,index,uv,normal,stCoords);
        //vec3 tempHitPoint = hitPoint;
        switch(hitObject->material.type){
            default:
                hitColor = computeDiffuse(ray,hitObject,hitPoint,stCoords,normal,index,modelSet,lights);
                break;
        }
    }
    return hitColor;
}



void RayTracer::gpuRender(Scene scene,Camera camera) {

}

//Function based heavily on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
bool RayTracer::trace(Ray &ray, vector<Model*> &modelSet, float &tNear, int &index, vec2 &uv, Model **hitObject) {
    *hitObject = nullptr;
    for (int i = 0; i < modelSet.size(); ++i) {
        float tNearI = ray.getTimeValueMax();
        int indexI;
        vec2 uvI;
        //modelSet[i]->intersect(ray,tNearI,indexI,uvI);
        if(modelSet[i]->intersect(ray,tNearI,indexI,uvI) && tNearI<tNear){
            //cout<<"i"<<endl;
            *hitObject = modelSet[i];
            tNear = tNearI;
            index = indexI;
            uv = uvI;
        }
    }

    return (*hitObject != nullptr);
}

vec3 RayTracer::computeDiffuse(Ray &ray, Model *hitObject, vec3 &tvec3, vec2 &stCoords, vec3 &normal, int &index, vector<Model*> modelSet, Light &lights) {

    vec3 lightAmt = vec3(10);
    vec3 specularColor = vec3(0);

    vec3 hitColor = (lightAmt * hitObject->evalDiffuseColor(stCoords) * hitObject->material.diffuse + specularColor * hitObject->material.specular);

    return hitColor;
}
