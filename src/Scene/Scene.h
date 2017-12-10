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
#include "Shading/Light.h"
//#include "Models/ModelSet.h"


using namespace glm;
using namespace std;
class Scene {
private:
    //vector<Model> modelObjects;
    vector<Sphere> modelSpheres;
    vector<Mesh> modelMeshes;
    vector<Light*> lights;
    //ModelSet modelObjects;

    //Setup the initial scene
    void generateDefaultScene();
    void generateMyScene();
    void loadConfig(string config);

public:
    Scene() = default;
    ~Scene() = default;

    void setupScene(string &sceneType);

    void addSphere(highp_vec3 pos, int radius, Material material);

    //bool isIntersect(Intersect &intersection);

    vector<Sphere> getSpheres();
    vector<Mesh> getMeshes();
    //ModelSet getModelObjects();
    //void addPlane();
    //void addCube();
    //void addSquare();
    vector<Light *> getLights();

    void genDefaultSquares();

    void genDefaultLights();

    void addSquare(Mesh &squareMesh, vec3 vert0, vec3 vert1, vec3 vert2, vec3 vert3, vec3 tvec31);

    void genDefaultSpherers();
};


#endif //ASSIGNMENT4_SCENE_H
