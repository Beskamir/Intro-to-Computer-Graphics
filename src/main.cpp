//
// Main function which calls all the other stuff
//

//Include all the needed libraries
#include <iostream>


//#include "OpenGL/mainOpenGL.h"
#include "Raytracer/RayTracer.h"
#include "Scene/Scene.h"
#include "Raytracer/ImageData.h"



using namespace std;

int main(int argc, char *argv[]) {
    string sceneType = argv[1];

    int width = 1024;
    int height = 1024;
    //double pi = 3.14159265358979323846264338327950288;

    //Setup final output image
    ImageData imageData(width, height);
    //Setup the camera
    Camera camera(vec3(278, 273, -500),vec3(278, 273, 0),vec3(1,0,0),55,(float)width/(float)height);

    Scene scene;
    scene.setupScene(sceneType);

    RayTracer rayTracer(2,width,height,5,vec3(1));
    rayTracer.cpuRender(&imageData, camera, scene);
    //cout<<sceneType<<endl;

    imageData.writeToPPM(sceneType);

    //return mainOpenGL(argc,argv);
    return 0;
}