//
// Scene class containing all the models and lights within the scene
//

#include "Scene.h"

#include <fstream>

void Scene::setupScene(string &sceneType) {
    if(sceneType=="--default"){
        sceneType = "default";
        generateDefaultScene();
    } else if(sceneType=="--yours"){
        sceneType = "yours";
        generateMyScene();
    } else{
        sceneType = "custom";
        loadConfig(sceneType);
    }
}

void Scene::generateMyScene() {

}

void Scene::generateDefaultScene() {
    addSphere(vec3(400, 130, 320),120);
    //addSquare(vec3(550,0,0),vec3(0,0,0),vec3(0,0,560),vec3(550,0,560));
    //addSquare(vec3((560,550,0)),vec3(560,550,560),vec3(0,550,560),vec3(550,0,560));
    //addSquare(vec3(550, 0, 560),vec3(0, 0, 560),vec3(0, 550, 560),vec3(560, 550, 560));
    //addSquare(vec3(0, 0, 560), vec3(0, 0, 0), vec3(0, 550, 0), vec3(0, 550, 560));
    //addSquare(vec3(550, 0, 0), vec3(550, 0, 560), vec3(560, 550, 560), vec3(560, 550, 0));

}

void Scene::loadConfig(string config) {
    ifstream file;
    file.open(config, fstream::in );
    if ( file.fail() ) {
        cout << "ERROR: Couldn't load \""
             << config << "\"." << endl;
    }
    string line;
    int counter = -1;
    while(getline(file,line)){
        //cout<<line<<endl;
        //Create model and add it to model objects
        if(line.substr(0,4)=="####"){
            Mesh model;
            modelMeshes.push_back(model);
            counter++;
        }
        //give a model its mesh data:
        if(line.substr(0,4)==">M: "){
            modelMeshes[counter].addModel(line.substr(4, line.size()-1));
        }
        //give a model it's texture data:
        if(line.substr(0,4)==" D: "){
            modelMeshes[counter].addTexture('d',line.substr(4, line.size()-1));
        }
        if(line.substr(0,4)==" A: "){
            modelMeshes[counter].addTexture('a',line.substr(4, line.size()-1));
        }
        if(line.substr(0,4)==" S: "){
            modelMeshes[counter].addTexture('s',line.substr(4, line.size()-1));
        }
    }
}

void Scene::addSphere(vec3 pos, float radius) {
    Sphere sphere(pos,radius);
    modelSpheres.push_back(sphere);
}

vector<Sphere> Scene::getSpheres() {
    return modelSpheres;
}

vector<Mesh> Scene::getMeshes() {
    return modelMeshes;
}
