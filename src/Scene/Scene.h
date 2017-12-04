//
// Scene class containing all the models and lights within the scene
//

#ifndef ASSIGNMENT4_SCENE_H
#define ASSIGNMENT4_SCENE_H
#include <iostream>
#include <vector>

//Include GLM for all the vector data.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//#include "Model.h"
#include "Models/Mesh.h"
#include "Models/Sphere.h"


using namespace glm;
using namespace std;
class Scene {
private:
    //vector<Model> modelObjects;
    vector<Sphere> modelSpheres;
    vector<Mesh> modelMeshes;

    //Setup the initial scene
    void generateDefaultScene();
    void generateMyScene();
    void loadConfig(string config);

public:
    Scene() = default;
    ~Scene() = default;

    void setupScene(string &sceneType);

    void addSphere(vec3 pos=vec3(0,0,0),float radius=1.0f);

    vector<Sphere> getSpheres();
    vector<Mesh> getMeshes();
    //void addPlane();
    //void addCube();
    //void addSquare();
};


#endif //ASSIGNMENT4_SCENE_H
