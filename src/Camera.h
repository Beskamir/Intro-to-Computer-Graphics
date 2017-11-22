//
// Camera class heavily based on: https://learnopengl.com/code_viewer.php?type=header&code=camera
//

#ifndef ASSIGNMENT2_CAMERA_H
#define ASSIGNMENT2_CAMERA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

//Modified to do it for both Windows and non-windows.
#ifdef _WIN32
#include <GL/glew.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#endif
//Include glfw
#include <GLFW/glfw3.h>

//Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"

using namespace std;
using namespace glm;

class Camera {
private:
    vec3 cameraPosition = vec3(0.0f, 0.0f, 0.0f);
    vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
    vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
    //vec3 cameraRight = vec3(0.0f, 0.0f, 0.0f);
    //vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);

    float cameraSpeed = 0.05f;
    float cameraFOV = 45.0f;

    GLfloat xRoll = -90.0f;
    GLfloat yRoll = 0.0f;

    struct Movement{
        bool forward;
        bool backward;
        bool right;
        bool left;
    };

    //void updateCameraVectors();

public:
    Camera()= default;
    void initalCameraLocation(Model model);

    //void centerView(int scaleX, int scaleY);
    //void fpsMouseMovement();
    //void moveCamera(bool forward, bool backward, bool right, bool left);
    void moveCamera(Movement movement, float deltaTime);
    void rotateView(vec2 mouseOffset);
    void centerView(Model model);
    void changeCameraSpeed(float changeSpeed);

    void setupCameraTransformationMatrices(GLint viewLocation, GLint projectionLocation, GLint viewPosLoc, int window_width, int window_height);

    ~Camera()= default;

    //mat4 getViewMatrix();
};


#endif //ASSIGNMENT2_CAMERA_H
