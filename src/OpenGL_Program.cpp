//
// Main OpenGL Program, does all the input handling and setup of the models
//

#include "OpenGL_Program.h"

void OpenGL_Program::mainRender(){
    // Define the viewport dimensions
    glViewport(0, 0, *window_width, *window_height);

    //forloop to open all the models and textures
    //Model model = Model("data/models/sphereTest.obj");
    //Model model = Model("data/models/pyramidTest.obj");
    Model model = Model("data/models/offical/chess_king/king.obj");
    model.addTexture("data/imageData/Tower.png");
    initalCameraLocation(model);

    modelObjects.push_back(model);

    // main render loop, keeps running until window is closed
    while (!glfwWindowShouldClose(window)){
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        //Render to screen loop
        renderToScreen(modelObjects);
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
}

void OpenGL_Program::renderToScreen(vector<Model> modelObjects) {
    // clear screen to a dark grey colour
    glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Cull triangles which normal is not towards the camera.
    // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
    glEnable(GL_CULL_FACE);
    mShaders.use();
    // Camera/View transformation
    glm::mat4 view;
    view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    GLint viewLoc = glGetUniformLocation(mShaders.id, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection;
    projection = glm::perspective(45.0f, (GLfloat)*window_width / (GLfloat)*window_height, 0.1f, 100.0f);
    GLint projLoc = glGetUniformLocation(mShaders.id, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLint modelLoc = glGetUniformLocation(mShaders.id, "modelTransformation");
    for (int i = 0; i < modelObjects.size(); ++i) {
        modelObjects[i].drawModel(modelLoc);
        //drawModel(modelObjects[i]); //draw the object
        //setTextureUsage(1);
    }
    glUseProgram(0); //cleanup
}

void OpenGL_Program::init_Program(GLFWwindow *window, int *window_width, int *window_height) {
    this->window=window;
    this->window_width=window_width;
    this->window_height=window_height;

    //ShaderProgram mShaders();
    // Build and compile the shader programs
    if (!mShaders.attachShader("data/shaderData/vertex.glsl", GL_VERTEX_SHADER))
        cout << "Error attaching vertex shader"<<endl;
    if (!mShaders.attachShader("data/shaderData/fragment.glsl", GL_FRAGMENT_SHADER))
        cout << "Error attaching fragment shader"<<endl;
    if (!mShaders.link())
        cout<<"Error linking shader program"<<endl;
}

void OpenGL_Program::moveCamera() {
    if(fpsMode){
        if(movement.forward){
            cameraPosition += cameraSpeed * cameraFront;
        }
        if(movement.backward){
            cameraPosition -= cameraSpeed * cameraFront;
        }
        if(movement.right){
            cameraPosition += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if(movement.left){
            cameraPosition -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
        }
    }
}

void OpenGL_Program::changeCameraSpeed(float changeSpeed) {
    float newCameraSpeed=cameraSpeed+changeSpeed;
    if(newCameraSpeed>0){
        cameraSpeed=newCameraSpeed;
    }
}

void OpenGL_Program::initalCameraLocation(Model model) {
    //cameraPosition = model.origin;
    cameraPosition.z += model.boundingBox.zCoord[0];
    float moveBackBy;
    if (abs(model.boundingBox.yCoord[0]) > abs(model.boundingBox.xCoord[0])) {
        moveBackBy = abs(model.boundingBox.yCoord[0]);
    } else {
        moveBackBy = abs(model.boundingBox.xCoord[0]);
    }
    cameraPosition.z += moveBackBy + (1 / model.boundingBox.zCoord[0]); //This seems to work pretty well
}

void OpenGL_Program::rotateView(float xOffset, float yOffset) {
    //cout<< xOffset<<":"<<yOffset<<endl;
    GLfloat sensitivity = 25;	// Change this value to your liking
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f){
        pitch = 89.0f;
    }
    if (pitch < -89.0f){
        pitch = -89.0f;
    }

    vec3 front = vec3(cos(radians(yaw)) * cos(radians(pitch)),
                      sin(radians(pitch)),
                      sin(radians(yaw)) * cos(radians(pitch)));
    cameraFront = normalize(front);
}

void OpenGL_Program::centerView(int scaleX, int scaleY) {
    //modelObjects[0].centerView(scaleX, scaleY);
}

void OpenGL_Program::scaleModel(vec3 scaleVec) {
    modelObjects[0].scaleModel(scaleVec);
}

void OpenGL_Program::finalizeTransformation() {
    if(scaleMode||rotateMode||moveMode){
        modelObjects[0].finalizeModelingTransformation();
    }
}

void OpenGL_Program::handleKeyPress(int key) {
    if (key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if(key==GLFW_KEY_F && !(rotateMode || scaleMode || moveMode)){
        mouseLocLast = getMouseLocation();
        fpsMode = !fpsMode;
        movement= {false,false,false,false};
    }
    else if(fpsMode){
        if(key==GLFW_KEY_W){
            movement.forward = true;
            movement.backward = false;
        }if(key==GLFW_KEY_S){
            movement.backward = true;
            movement.forward = false;
        }if(key==GLFW_KEY_A){
            movement.left = true;
            movement.right = false;
        }if(key==GLFW_KEY_D){
            movement.right = true;
            movement.left = false;
        }
    }
    else if(!fpsMode){
        if(key==GLFW_KEY_S && !scaleMode){
            mouseLocLast = getMouseLocation();
            mousePerpendicular = vec2(-mouseLocLast.y,mouseLocLast.x);
            cout << mouseLocLast.x <<":"<<mouseLocLast.y<<endl;
            cout << mousePerpendicular.x << ":" << mousePerpendicular.y<<endl;
            initalMouseDistance = getMouseDistance(mouseLocLast);
            scaleMode = true;
            rotateMode = false;
            moveMode = false;
            useAxis={true,true,true};
        }else if(key==GLFW_KEY_R && !rotateMode){
            mouseLocLast = getMouseLocation();
            rotateMode = true;
            moveMode = false;
            scaleMode = false;
            useAxis={true,true,true};
        }else if(key==GLFW_KEY_G && !moveMode){
            mouseLocLast = getMouseLocation();
            moveMode = true;
            rotateMode = false;
            scaleMode = false;
            useAxis={true,true,true};
        }
        else if(rotateMode||scaleMode||moveMode){
            if(key==GLFW_KEY_LEFT_SHIFT||key==GLFW_KEY_RIGHT_SHIFT){
                shiftMode=!shiftMode;
            }//Lock to one of the following axis
            else if(key==GLFW_KEY_X){
                if(shiftMode){
                    useAxis={false, true, true};
                    //cout<<"locking to y,z"<<endl;
                }else{
                    useAxis={true, false, false};
                    //cout<<"locking to x"<<endl;
                }
            }else if(key==GLFW_KEY_Y){
                if(shiftMode){
                    useAxis={true, false, true};
                }else{
                    useAxis={false, true, false};
                }
            }else if(key==GLFW_KEY_Z){
                if(shiftMode){
                    useAxis={true, true, false};
                }else{
                    useAxis={false, false, true};
                }
            }else if(key==GLFW_KEY_A){
                useAxis={true,true,true};
            }
        }
        else if(key==GLFW_KEY_C){
            //Center view on object
            int scaleX = 1;
            int scaleY = 1;
            centerView(scaleX,scaleY);
        }
    }
}
vec2 OpenGL_Program::getMouseLocation() {
    double xpos,ypos;
    glfwGetCursorPos(window, &xpos,&ypos);
    vec2 mouseLocation={(2.0f*((float)(xpos)/(*window_width)))-1.0f,
                        1.0f-(2.0f*((float)(ypos)/(*window_height)))};
    return mouseLocation;
}

double OpenGL_Program::getPositivity() {
    double expected_y = (mouseLocEndless.x * (mousePerpendicular.y / mousePerpendicular.x));
    //double expected_y = (((mouseLocCurrent.x*(abs(xTeleportCounter)+1)) * (mousePerpendicular.y / mousePerpendicular.x))/(abs(yTeleportCounter)+1));
    if(mouseLocEndless.y>0){
        if (expected_y > mouseLocEndless.y) {
            return -1;
        } else {
            return 1;
        }
    }else{
        if (expected_y < mouseLocEndless.y ) {
            return -1;
        } else {
            return 1;
        }
    }
}

double OpenGL_Program::getMouseDistance(vec2 mousePosition) {
    return sqrt(pow(mousePosition.x,2)+pow(mousePosition.y,2));
}

void OpenGL_Program::teleportMouse(double xpos, double ypos) {
    mouseLocCurrent=getMouseLocation();
    if (mouseLocCurrent.x < -0.75) {
        xTeleportCounter--;
        glfwSetCursorPos(window, ((0.7 + 1.0) / 2) * *window_width, ypos);
    }
    if (mouseLocCurrent.x > 0.75) {
        xTeleportCounter++;
        glfwSetCursorPos(window, ((-0.7 + 1.0) / 2) * *window_width, ypos);
    }
    if (mouseLocCurrent.y < -0.75) {
        yTeleportCounter--;
        glfwSetCursorPos(window, xpos, ((0.7 - 1.0) / 2) * -*window_height);
    }
    if (mouseLocCurrent.y > 0.75) {
        yTeleportCounter++;
        glfwSetCursorPos(window, xpos, ((-0.7 - 1.0) / 2) * -*window_height);
    }
    setMouseLocationEndlessGraph();
}

void OpenGL_Program::setMouseLocationEndlessGraph() {
    mouseLocLast = getMouseLocation();
    if (xTeleportCounter < 0) {
        mouseLocEndless.x = (abs(mouseLocLast.x) * (xTeleportCounter - 1));
    } else if (xTeleportCounter > 0) {
        mouseLocEndless.x = (abs(mouseLocLast.x) * (xTeleportCounter + 1));
    } else {
        mouseLocEndless.x = mouseLocLast.x;
    }
    if(yTeleportCounter<0){
        mouseLocEndless.y = (abs(mouseLocLast.y) * (yTeleportCounter - 1));
    } else if (yTeleportCounter>0) {
        mouseLocEndless.y = (abs(mouseLocLast.y) * (yTeleportCounter - 1));
    }else{
        mouseLocEndless.y = mouseLocLast.y;
    }
}

void OpenGL_Program::fpsMouseMovement(){
    mouseLocCurrent = getMouseLocation();
    rotateView(mouseLocCurrent.x-mouseLocLast.x,
               mouseLocCurrent.y-mouseLocLast.y);
    glfwSetCursorPos(window,*window_width/2,*window_height/2);
    //mouseLocCurrent = getMouseLocation();
    //cout<<mouseLocCurrent.x<<":"<<mouseLocCurrent.y<<endl;
    //cout<<mouseLocLast.x<<":"<<mouseLocLast.y<<endl;
    mouseLocLast = getMouseLocation();
}

void OpenGL_Program::checkForTransformations(double xpos, double ypos) {
    if(scaleMode){
        teleportMouse(xpos,ypos);
        mouseLocCurrent = getMouseLocation();
        //mouseLocCurrent.x*=(abs(xTeleportCounter)+1);
        //mouseLocCurrent.y*=(abs(yTeleportCounter)+1);
        double scaleFactor = getPositivity() * getMouseDistance(mouseLocEndless) / initalMouseDistance;
        //cout<<scaleFactor<<endl;
        vec3 scaleVec(scaleFactor,scaleFactor,scaleFactor);
        scaleModel(scaleVec);
    }
    if(rotateMode){
        mouseLocCurrent = getMouseLocation();
        //openGL_program.rotateModel(mouseLocCurrent.x-mouseLocLast.x,
        //                          mouseLocCurrent.y-mouseLocLast.y);
        //cout<<mouseLocCurrent.x<<":"<<mouseLocCurrent.y<<endl;
        //cout<<mouseLocLast.x<<":"<<mouseLocLast.y<<endl;
        mouseLocLast = mouseLocCurrent;
    }
    if(moveMode){

    }
}

void OpenGL_Program::handleKeyRelease(int key) {
    //cout<<key<<endl;
    if(key==GLFW_KEY_W){
        movement.forward = false;
    }
    else if(key==GLFW_KEY_S){
        movement.backward = false;
    }
    else if(key==GLFW_KEY_A){
        movement.left = false;
    }
    else if(key==GLFW_KEY_D){
        movement.right = false;
    }
}

void OpenGL_Program::handleMouseMovement(double xpos, double ypos) {
    if(fpsMode){
        //mouseLocCurrent=getMouseLocation();
        //teleportMouse(xpos,ypos);
        fpsMouseMovement();
    }
    else{
        checkForTransformations(xpos,ypos);
    }
}

//void OpenGL_Program::scaleWithWindow(float scaleX, float scaleY) {
//    //modelObjects[0].scaleWithWindow(scaleX,scaleY);
//}
