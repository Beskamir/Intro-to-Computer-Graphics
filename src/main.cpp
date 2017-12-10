//
// Main function which calls all the other stuff
//

//Include all the needed libraries
#include <iostream>


//#include "OpenGL/mainOpenGL.h"
#include "Raytracer/RayTracer.h"
#include "Scene/Scene.h"
#include "Raytracer/ImageData.h"


void setupUserDefinedVars(int &width, int &height, int &fieldOfView, int &bounceDepth, int &samples);

void getUserInput(int &width, int defaultValue);

using namespace std;

int main(int argc, char *argv[]) {
    string sceneType = argv[1];

    int width, height, fieldOfView, bounceDepth, superSampling;
    vec3 background = vec3(0);
    //vec3 background = vec3(0.2,0.4,1);

    setupUserDefinedVars(width,height,fieldOfView,bounceDepth,superSampling);

    //Setup final output image
    ImageData imageData(width, height);
    //Setup the camera
    Camera camera(vec3(278, 273, -500),vec3(278, 273, 0),vec3(1,0,0),fieldOfView,(float)height/(float)width);

    Scene scene;
    scene.setupScene(sceneType);

    RayTracer rayTracer(superSampling,width,height,bounceDepth,background);
    rayTracer.cpuRender(&imageData, camera, scene);
    //cout<<sceneType<<endl;

    imageData.writeToPPM(sceneType);

    //return mainOpenGL(argc,argv);
    return 0;
}

void setupUserDefinedVars(int &width, int &height, int &fieldOfView, int &bounceDepth, int &samples) {
    cout<<"The user can specify a bunch of values by typing them into the console and pressing enter following each prompt. "
            "\nNotes: "
            "\n\t- Pressing enter will use a default value. "
            "\n\t- There is absolutely no error checking so in theory "
            "\n\t   the user can ask for say a negative field of view "
            "\n\t   and if things break it's their fault for being stupid.\n"<<endl;
    cout<<"Enter image width: \n\t(Integer value greater than 0; \n\tDefault = 512)\n> ";
    getUserInput(width,512);

    cout<<"Enter image height: \n\t(Integer value greater than 0; \n\tDefault = 512)\n> ";
    getUserInput(height,512);

    cout<<"Enter field of view: \n\t(Integer value greater than 0 and less than 90; \n\tDefault = 55)\n> ";
    getUserInput(fieldOfView,55);

    cout<<"Enter tracing depth: \n\t(Integer value greater than 0; \n\tDefault = 8)\n> ";
    getUserInput(bounceDepth,8);

    cout<<"Enter square root of the number of samples per pixel: \n\t(Integer value greater than 0; \n\tDefault = 2; \n\t'square root' meaning enter 2 if you want 4 sample per pixel, 3 if you want 9, 4 if 16, etc.)\n> ";
    getUserInput(samples,2);

}

void getUserInput(int &newValue, int defaultValue) {
    string userInput;
    ///temp disabling this for my own sanity, reenable it later!!
    //getline(cin,userInput);
    if(userInput.empty()){
        newValue=defaultValue;
    }else{
        stringstream potentialWidth(userInput);
        potentialWidth >> newValue;
    }
}