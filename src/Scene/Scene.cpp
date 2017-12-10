//
// Scene class containing all the models and lights within the scene
//

#include "Scene.h"
#include "Shading/PointLight.h"
#include "Shading/DirectionalLight.h"

#include <fstream>

void Scene::setupScene(string &sceneType) {
    //cout<<sceneType<<endl;
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
    Mesh mesh;
    //cout<<"myscene"<<endl;
    mesh.addModel("data/models/pTest01.obj");
    modelMeshes.push_back(mesh);
    //cout<<"addinglights"<<endl;
    genDefaultLights();
}

void Scene::generateDefaultScene() {
    genDefaultSpherers();
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

void Scene::addSphere(highp_vec3 pos, int radius, Material material) {
    Sphere sphere(pos,radius);
    sphere.material = material;
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

void Scene::addSquare(Mesh &squareMesh, vec3 vert0, vec3 vert1, vec3 vert2, vec3 vert3, vec3 normal) {
    //Mesh tempSquare;
    squareMesh.addTriangle({vert0,vert1,vert3},normal);
    squareMesh.addTriangle({vert1,vert2,vert3},normal);
    //modelMeshes.push_back(tempSquare);
}

void Scene::genDefaultSquares() {
    Material material;

    //all the points for the walls
    vec3 p0 = vec3(0,   0,   0);
    vec3 p1 = vec3(550, 0,   0);
    vec3 p2 = vec3(0,   0,   560);
    vec3 p3 = vec3(550, 0,   560);
    vec3 p4 = vec3(560, 550, 0);
    vec3 p5 = vec3(560, 550, 560);
    vec3 p6 = vec3(0,   550, 560);
    vec3 p7 = vec3(0,   550, 0);

    //all the normals for the walls
    vec3 n0 = vec3(0.0,-1.0,0.0);
    vec3 n1 = vec3(0.0,1.0,0.0);
    vec3 n2 = vec3(1.0,0.0,0.0);
    vec3 n3 = vec3(-1.0,0.0,0.0);
    vec3 n4 = vec3(0.0,0.0,-1.0);

    //Setup bottom wall
    Mesh bottomWall;
    material.setDiffuseColor(vec3(0.25));
    material.setSpecularColor(vec3(0.25));
    bottomWall.material=material;
    addSquare(bottomWall, p1, p0, p2, p3, n1);
    modelMeshes.push_back(bottomWall);

    //setup back wall
    Mesh backWall;
    material.setDiffuseColor(vec3(0.35,0.45,0.2));
    backWall.material=material;
    //addSquare(backWall, p3, p2, p6, p5, n4);
    addSquare(backWall, p6, p5, p3, p2, n4);
    modelMeshes.push_back(backWall);

    //setup left wall
    Mesh leftWall;
    material.setDiffuseColor(vec3(0.0,0.25,0.25));
    leftWall.material=material;
    addSquare(leftWall, p2, p0, p7, p6, n2);
    modelMeshes.push_back(leftWall);

    //setup right wall
    Mesh rightWall;
    material.setMaterialType(REFLECTION);
    //material.setDiffuseColor(vec3(0.35,0.45,0.2));
    rightWall.material=material;
    addSquare(rightWall, p1, p3, p5, p4, n3);
    modelMeshes.push_back(rightWall);
    material.setMaterialType(PHONG);

    //don't include the top to let light in
    //Mesh top;
    //top.material=material;
    //addSquare(top, p4, p5, p6, p7, n1);
    //modelMeshes.push_back(top);


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

    //addSphere(vert0,10.0f);
    //addSphere(vert1,10.0f);
    //addSphere(vert2,10.0f);
    //addSphere(vert3,10.0f);
    //addSphere(vert4,10.0f);
    //addSphere(vert5,10.0f);
    //addSphere(vert6,10.0f);
    //addSphere(vert7,10.0f);

    Mesh squareMesh;
    material.setDiffuseColor(vec3(0.85,0.55,0.1));
    material.setSpecularColor(vec3(0.5));
    //material.setIndexOfRefraction(1);
    material.setMaterialType(REFLECTION_AND_REFRACTION);
    squareMesh.material = material;
    //add all the sides of the smaller square
    addSquare(squareMesh, vert3, vert1, vert5, vert7, normal0); //top
    //addSquare(squareMesh, vert7, vert5, vert1, vert3, normal0); //top
    addSquare(squareMesh, vert4, vert5, vert7, vert6, normal4); //right side
    addSquare(squareMesh, vert2, vert3, vert7, vert6, normal3); //front
    addSquare(squareMesh, vert2, vert3, vert1, vert0, normal1); //left side
    //addSquare(squareMesh, vert0, vert1, vert3, vert2, normal1); //left side
    addSquare(squareMesh, vert0, vert1, vert5, vert4, normal2); //back
    modelMeshes.push_back(squareMesh);
}

void Scene::genDefaultLights() {
    //Material material;
    //material.setDiffuseColor(vec3(100));
    //material.setMaterialType(LIGHT);

    lights.push_back(new PointLight(vec3(185.0,2000.0,169.0),vec3(1)));
    //addSphere(vec3(185.0,2000.0,169.0),100,material);

    lights.push_back(new PointLight(vec3(400.0,2000.0,320.0),vec3(1)));
    //addSphere(vec3(400.0,2000.0,320.0),100,material);

    //lights.push_back(new PointLight(vec3(400.0,200.0,320.0),vec3(1)));
    //lights.push_back(new DirectionalLight(vec3(278, 273, -150),vec3(1)));
}

void Scene::genDefaultSpherers() {
    Material material;
    material.setMaterialType(REFLECTION_AND_REFRACTION);
    //material.indexOfRefraction = 1.5;
    material.setIndexOfRefraction(1.5);
    material.setDiffuseColor(vec3(1,0.3,0.15));
    //material.setDiffuseColor(vec3(1));
    material.setSpecularColor(vec3(0.5));
    addSphere(vec3(400, 130, 320), 120, material);
}
