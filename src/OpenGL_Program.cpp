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
    camera.initalCameraLocation(model);
    //initalCameraLocation(model);

    modelObjects.push_back(model);

    //GLfloat deltaTime = 0.0f;
    //GLfloat lastFrame = 0.0f;
    //GLfloat currentFrame = 0.0f;
    // main render loop, keeps running until window is closed
    while (!glfwWindowShouldClose(window)){
        // Set frame time
        //glfwGetTime();
        //currentFrame = (GLfloat)glfwGetTime();
        //deltaTime = currentFrame - lastFrame;
        //lastFrame = currentFrame;

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        moveCameraWASD(1.0f);

        //Render to screen loop
        renderToScreen(modelObjects);
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
}

void OpenGL_Program::renderToScreen(vector<Model> modelObjects) {
    // clear screen to a dark grey colour
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Cull triangles which normal is not towards the camera.
    // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
    glEnable(GL_CULL_FACE);

    mShaders.use();
    // Camera/View transformation
    GLint viewLoc = glGetUniformLocation(mShaders.id, "view");
    GLint projLoc = glGetUniformLocation(mShaders.id, "projection");
    camera.setupCameraTransformationMatrices(viewLoc,projLoc,*window_width,*window_height);

    //cout<<"drawing model: "<<endl;
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

void OpenGL_Program::handleKeyCallback(int key, int action) {
    if(key>=0&&key<1024){
        if(action == GLFW_PRESS){
            activeKeys[key] = true;
            handleKeyPress(key);
        }
        else if(action == GLFW_RELEASE){
            activeKeys[key] = false;
        }
    }
}

void OpenGL_Program::handleKeyPress(int key) {
    if (key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if(key==GLFW_KEY_F && !(modes.rotate || modes.scale || modes.move)){
        //mouseLocLast = getMouseLocation();
        modes.fps = !modes.fps;
        //movement= {false,false,false,false};
    }
    else if(modes.fps){
        //if(key==GLFW_KEY_W){
        //    movement.forward = true;
        //    movement.backward = false;
        //}if(key==GLFW_KEY_S){
        //    movement.backward = true;
        //    movement.forward = false;
        //}if(key==GLFW_KEY_A){
        //    movement.left = true;
        //    movement.right = false;
        //}if(key==GLFW_KEY_D){
        //    movement.right = true;
        //    movement.left = false;
        //}
    }

}

void OpenGL_Program::handleScrollCallback(double yoffset) {
    float scalingSpeed=0.0025f;
    if(yoffset>0){
        camera.changeCameraSpeed(scalingSpeed);
    }
    if(yoffset<0){
        camera.changeCameraSpeed(-scalingSpeed);
    }

}

void OpenGL_Program::moveCameraWASD(double deltaTime) {
    if(modes.fps){
        //Pass along {W,S,D,A} == {forward, backward, right, left}
        camera.moveCamera({activeKeys[GLFW_KEY_W],activeKeys[GLFW_KEY_S],activeKeys[GLFW_KEY_D],activeKeys[GLFW_KEY_A]}, (float) deltaTime);
    }
}

void OpenGL_Program::handleMouseMovement(double xpos, double ypos) {

}

void OpenGL_Program::finalizeTransformation() {

}
//void OpenGL_Program::scaleWithWindow(float scaleX, float scaleY) {
//    //modelObjects[0].scaleWithWindow(scaleX,scaleY);
//}
