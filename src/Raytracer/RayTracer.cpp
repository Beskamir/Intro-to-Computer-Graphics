//
// This will run the ray tracing algorithm
//

#include "RayTracer.h"
#include "Color.h"
#include "ImageData.h"
#include "Ray.h"

void RayTracer::cpuRender(ImageData *image, Camera camera, Scene scene) {

    vector<Sphere> modelSpheres = scene.getSpheres();
    vector<Mesh> modelMeshes = scene.getMeshes();
    ModelSet modelSet;
    for (int i = 0; i < modelSpheres.size(); ++i) {
        modelSet.addModel(&modelSpheres[i]);
    }
    for (int j = 0; j < modelMeshes.size(); ++j) {
        modelSet.addModel(&modelMeshes[j]);
    }

    //modelObjects[0].
    vec3 distance;
    for (int x = 0; x < image->getWidth(); ++x) {
        for (int y = 0; y < image->getHeight(); ++y) {
            vec2 screenCoord((2.0f*x) / image->getWidth() - 1.0f,
                             (-2.0f*y) / image->getHeight() + 1.0f);

            Ray ray = camera.generateRay(screenCoord);
            Color pixel = Color(0.5); //create pixel

            Intersection intersection(ray);
            if(modelSet.intersect(intersection)){
                pixel = intersection.getColor();
            }
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
    
    
    //Sphere sphere
}

void RayTracer::gpuRender(Scene scene,Camera camera) {

}
