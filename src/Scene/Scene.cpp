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

    //smaller square verts
    vec3 vert0 = vec3(52,  0,   225);
    vec3 vert1 = vec3(52,  165, 225);

    vec3 vert2 = vec3(100, 0,   65);
    vec3 vert3 = vec3(100, 165, 65);

    vec3 vert4 = vec3(210, 0,   272);
    vec3 vert5 = vec3(210, 165, 272);

    vec3 vert6 = vec3(260, 0,   114);
    vec3 vert7 = vec3(260, 165, 114);

    //smaller square normals
    vec3 normal0 = vec3(0.0,1.0,0.0);
    vec3 normal1 = vec3(0.0,0.0,-1.0);
    vec3 normal2 = vec3(-1.0,0.0,0.0);
    vec3 normal3 = vec3(1.0,0.0,0.0);
    vec3 normal4 = vec3(0.0,0.0,1.0);

    Mesh squareMesh;
    //add all the sides of the smaller square
    //addSquare(squareMesh, vert3, vert1, vert5, vert7, normal0);
    //addSquare(squareMesh, vert6, vert7, vert5, vert4, normal1);
    //addSquare(squareMesh, vert2, vert3, vert7, vert6, normal2);
    //addSquare(squareMesh, vert0, vert1, vert3, vert2, normal3);
    addSquare(squareMesh, vert4, vert5, vert1, vert0, normal4);
    modelMeshes.push_back(squareMesh);
}

void Scene::genDefaultLights() {
    lights.push_back(new PointLight(vec3(185.0,2000.0,169.0),vec3(5)));
    lights.push_back(new PointLight(vec3(400.0,2000.0,320.0),vec3(5)));
    //lights.push_back(new PointLight(vec3(400.0,200.0,320.0),vec3(1000)));
    lights.push_back(new DirectionalLight(vec3(278, 273, -150),vec3(5)));
}

void Scene::addSquare(Mesh &squareMesh, vec3 vert0, vec3 vert1, vec3 vert2, vec3 vert3, vec3 normal) {
    Mesh tempSquare;
    squareMesh.addTriangle({vert0,vert1,vert3},normal);
    squareMesh.addTriangle({vert1,vert2,vert3},normal);
    //modelMeshes.push_back(tempSquare);
}