//
// Scene class containing all the models and lights within the scene
//

#include "Scene.h"
#include "Shading/PointLight.h"
#include "Shading/DirectionalLight.h"

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
    addSphere(vec3(400, 130, 320),120,Color(0,1,1,1));
    genDefaultLights();
    genDefaultSquares();



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
    //for (int i = 0; i < modelMeshes.size(); ++i) {
    //    modelObjects.addModel(modelMeshes[i]);
    //}
}

void Scene::addSphere(vec3 pos, float radius,Color color) {
    Sphere sphere(pos,radius,color);
    modelSpheres.push_back(sphere);
    //modelObjects.addModel(sphere);
}

vector<Sphere> Scene::getSpheres() {
    return modelSpheres;
}

vector<Mesh> Scene::getMeshes() {
    return modelMeshes;
}

vector<Light *> Scene::getLights() {
    return lights;
}

void Scene::genDefaultSquares() {
    //Generate points for the squares
    vec3 p1 = vec3(0,0,0);
    vec3 p2 = vec3(550,0,0);
    vec3 p3 = vec3(0,0,560);
    vec3 p4 = vec3(550,0,560);
    vec3 p5 = vec3(560,550,0);
    vec3 p6 = vec3(560,550,560);
    vec3 p7 = vec3(0,550,560);
    vec3 p8 = vec3(0,550,0);
    //Generate all the normals for the squares
    vec3 n1 = vec3(0.0,-1.0,0.0);
    vec3 n2 = vec3(0.0,1.0,0.0);
    vec3 n3 = vec3(1.0,0.0,0.0);
    vec3 n4 = vec3(-1.0,0.0,0.0);
    vec3 n5 = vec3(0.0,0.0,-1.0);

    Material material;
    Mesh squareMesh;
    // Add in bottom square
    squareMesh.addTriangle(p1,p3,p2,n2);
    squareMesh.addTriangle(p4,p2,p3,n2);
    // Add in top square
    squareMesh.addTriangle(p5,p7,p6,n1);
    squareMesh.addTriangle(p8,p7,p5,n1);
    // Add in left square
    squareMesh.addTriangle(p3,p1,p8,n3);
    squareMesh.addTriangle(p3,p8,p7,n3);
    // Add in back square
    squareMesh.addTriangle(p4,p3,p7,n5);
    squareMesh.addTriangle(p4,p7,p6,n5);

    //squareMesh.setMaterial(material);
    modelMeshes.push_back(squareMesh);

    Mesh rightSquare;
    // Add in right square
    rightSquare.addTriangle(p4,p2,p5,n4);
    rightSquare.addTriangle(p4,p5,p6,n4);
    modelMeshes.push_back(rightSquare);
}

void Scene::genDefaultLights() {
    lights.push_back(new PointLight(vec3(185.0,2000.0,169.0),vec3(5)));
    lights.push_back(new PointLight(vec3(400.0,2000.0,320.0),vec3(5)));
    //lights.push_back(new PointLight(vec3(400.0,200.0,320.0),vec3(1000)));
    //lights.push_back(new DirectionalLight(vec3(278, 273, -150),vec3(5)));
}

//ModelSet Scene::getModelObjects() {
//    return modelObjects;
//}
