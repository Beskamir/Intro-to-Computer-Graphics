//
// This will run the ray tracing algorithm
//

#include "RayTracer.h"
//#include "../Scene/Shading/Color.h"
//#include "ImageData.h"
//#include "Ray.h"
//#include "../Scene/Shading/Light.h"

RayTracer::RayTracer(int samples, int width, int height, int maxDepth,vec3 backgroundColor) {
    this->samples = samples;
    this->width = width;
    this->height = height;
    this->maxDepth = maxDepth;
    this->backgroundColor = backgroundColor;
}

void RayTracer::cpuRender(ImageData *image, Camera camera, Scene scene) {

    vector<Sphere> modelSpheres = scene.getSpheres();
    vector<Mesh> modelMeshes = scene.getMeshes();
    vector<Light*> lights = scene.getLights();
    vector<Model*> modelSet;
    for (int i = 0; i < modelSpheres.size(); ++i) {
        modelSet.push_back(&modelSpheres[i]);
    }
    for (int j = 0; j < modelMeshes.size(); ++j) {
        modelSet.push_back(&modelMeshes[j]);
    }
    int totalPixels = width * height;
    int lastPercent = -1;
    int currentPercent = -1;
    cout<<"\n\nBeginning CPU-Based Render:"<<endl;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            vec3 pixel = superSample(x,y,modelSet,camera,lights);
            image->storePixel(x, y, pixel);
        }
        currentPercent=(int)ceil(((float)(x*height)/(float)totalPixels)*100);
        if(currentPercent!=lastPercent){
            cout<<"Percent done: "<<currentPercent<<"%"<<endl;
            lastPercent = currentPercent;
        }
    }
}



// following function thanks to what was provided alongside the assignment.
// This function generates point on the image plane and starts a trace through them.
// Grid supersampling is also implemented.
vec3 RayTracer::superSample(int x, int y, vector<Model*> modelSet,Camera camera,vector<Light*> lights){
    vec2 windowCoord;
    vec3 color = backgroundColor;
    for(int i = 0; i < samples; i++){
        for(int j = 0; j < samples; j++){
            windowCoord.x = (float) x + (float)i/(float)samples;
            windowCoord.y = (float) y + (float)i/(float)samples;
            vec2 screenCoord((((2.0f * (windowCoord.x)) / (float)width) - 1.0f),
                             (1.0f - ((2.0f * (windowCoord.y)) / (float)height)));

            Ray ray = camera.generateRay(screenCoord);
            color = color + castRay(ray, modelSet, lights, 0);
        }
    }
    return color*(float)(1.0/float(samples*samples));;
}

//Function based heavily on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
vec3 RayTracer::castRay(Ray ray, vector<Model*> modelSet, vector<Light*> lights, int depth){
    vec3 hitColor = backgroundColor;
    if(depth > maxDepth){
        return hitColor;
    }
    float tNear = ray.getTimeValueMax();
    int index = 0;
    Model *hitObject = nullptr;
    vec2 uv;
    if(trace(ray,modelSet,tNear,index,uv,&hitObject)){
        //return vec3(1);
        vec3 hitPoint = ray.calculate(tNear);
        vec3 normal;
        vec2 stCoords;
        hitObject->getSurfaceProperties(hitPoint,ray,index,uv,normal,stCoords);
        //vec3 tempHitPoint = hitPoint;
        switch(hitObject->material.type){
            case REFLECTION_AND_REFRACTION:
                //vec3 reflection = computeReflection(ray,hitObject,hitPoint,stCoords,normal,index,modelSet,lights,uv);
                hitColor = computeReflection(ray,hitObject,hitPoint,stCoords,normal,index,modelSet,lights,uv)
                           + computeRefraction(ray,hitObject,hitPoint,stCoords,normal,index,modelSet,lights,uv);
                break;

            case REFLECTION:
                hitColor = computeReflection(ray,hitObject,hitPoint,stCoords,normal,index,modelSet,lights,uv);
                break;

            default:
                hitColor = computeDiffuse(ray,hitObject,hitPoint,stCoords,normal,index,modelSet,lights,uv);
                break;
        }
    }
    return hitColor;
}



vec3 RayTracer::computeDiffuse(Ray &ray, Model *hitObject, vec3 &hitPoint, vec2 &stCoords, vec3 &normal, int &index, vector<Model*> modelSet, vector<Light*> &lights, vec2 uv) {

    vec3 lightAmount = vec3(0);
    vec3 specularColor = vec3(0);
    vec3 shadowOrigin = dot(ray.getDirection(),normal)?
                        hitPoint + normal * biasValue :
                        hitPoint - normal * biasValue;

    for (int i = 0; i < lights.size(); ++i) {
        vec3 lightDirection = lights[i]->getDirection(hitPoint);

        float lightDistance = lengthSquared(lightDirection);
        lightDirection = normalize(lightDirection);

        float lightDotNormal = std::max(0.0f,dot(lightDirection,normal));
        Model *shadowHitObject = nullptr;
        float tNearShadow = ray.getTimeValueMax();

        Ray shadowRay(shadowOrigin,lightDirection);
        bool inShadow = trace(shadowRay,modelSet,tNearShadow,index,uv,&shadowHitObject) && (tNearShadow * tNearShadow < lightDistance);

        lightAmount += (float)(1-inShadow) * lights[i]->getColor() * lightDotNormal;
        vec3 reflectionDirection = reflect(-lightDirection,normal);
        specularColor += powf(std::max(0.f, -dot(reflectionDirection,ray.getDirection())),hitObject->material.specularExponent) * lights[i]->getColor();
    }

    vec3 hitColor = ((lightAmount * hitObject->material.evalDiffuseColor(stCoords))
                      + (specularColor * hitObject->material.specularColor));

    return hitColor;
}

vec3 RayTracer::computeReflection(Ray &ray, Model *hitObject, vec3 &hitPoint, vec2 &stCoords, vec3 &normal, int &index, vector<Model*> modelSet, vector<Light*> &lights, vec2 uv) {
    vec3 reflectedColor = vec3(0);

    //Fill in

    return reflectedColor;
}

vec3 RayTracer::computeRefraction(Ray &ray, Model *hitObject, vec3 &hitPoint, vec2 &stCoords, vec3 &normal, int &index, vector<Model*> modelSet, vector<Light*> &lights, vec2 uv) {
    vec3 refractedColor = vec3(0);

    //Fill in

    return refractedColor;
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
        //return true;
        //modelSet[i]->intersect(ray,tNearI,indexI,uvI);
        if(modelSet[i]->intersect(ray,tNearI,indexI,uvI) && tNearI<tNear){
            //cout<<"false"<<endl;
            //cout<<"i"<<endl;
            *hitObject = modelSet[i];
            tNear = tNearI;
            index = indexI;
            uv = uvI;
        }
    }

    return (*hitObject != nullptr);
}
