//
// Main OpenGL Program, does all the input handling and setup of the models
//

#include "OpenGL_Program.h"

void OpenGL_Program::mainRender(){
    // Define the viewport dimensions
    glViewport(0, 0, *window_width, *window_height);
    mouse = Mouse(window, window_width, window_height);

    //forloop to open all the models and textures
    //Model model;
    //Model model = Model("data/models/sphereTest.obj");
    //Model model = Model("data/models/offical/coffee_cup/coffee_cup.obj");
    //Model model = Model("data/models/pyramidTest.obj");
    //Model model = Model("data/models/offical/oak_chair/oak_chair.obj");
    //model.addModel("data/models/offical/chess_king/king.obj");
    //model.addTexture('d',"data/textures/testTexture.jpg");
    //model.addTexture("data/models/offical/oak_chair/oak_table.colour.jpg");
    //modelObjects.push_back(model);
    camera.initalCameraLocation(modelObjects[selected]);

    //camera.initalCameraLocation(model);

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

    mShaders.use();

    // Camera/View transformation
    GLint viewLoc = glGetUniformLocation(mShaders.id, "view");
    GLint projLoc = glGetUniformLocation(mShaders.id, "projection");
    GLint viewPosLoc = glGetUniformLocation(mShaders.id, "viewPos");
    camera.setupCameraTransformationMatrices(viewLoc,projLoc, viewPosLoc,*window_width,*window_height);

    //cout<<"drawing model: "<<endl;

    for (int i = 0; i < modelObjects.size(); ++i) {
        modelObjects[i].drawModel(mShaders,(modes.scale||modes.rotate||modes.move),worldAxis);
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
        modes={false,false,false,false};
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        //glfwSetWindowShouldClose(window, GL_TRUE);
    } else if (key == GLFW_KEY_F && !(modes.rotate || modes.scale || modes.move)) {
        //glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
        transformations.clear();
        mouse.reset();
        mouse.setMouseLast();
        modes.fps = !modes.fps;
        if(modes.fps){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else{
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    if(!modes.fps){
        handleNonFPS_Mode(key);
    }
}

void OpenGL_Program::handleNonFPS_Mode(int key) {
    if (modes.rotate || modes.scale || modes.move) {
        handleTransformationMode(key);
        tryActivatingTransformations(key);
    }
    else if(activeKeys[GLFW_KEY_LEFT_CONTROL]||activeKeys[GLFW_KEY_RIGHT_CONTROL]){
        handleTextureModes(key);
    }
    else{
        tryActivatingTransformations(key);
    }
}

void OpenGL_Program::tryActivatingTransformations(int key) {
    if (key == GLFW_KEY_S && !modes.scale) {
        transformations.clear();
        mouse.reset();
        mouse.setMouseLast();
        modes = {false, true, false, false};
        useAxis = {true, true, true};
    }
    if (key == GLFW_KEY_R && !modes.rotate) {
        transformations.clear();
        mouse.reset();
        mouse.setMouseLast();
        modes = {false, false, true, false};
        useAxis = {true, true, true};
    }
    if (key == GLFW_KEY_G && !modes.move) {
        transformations.clear();
        mouse.reset();
        mouse.setMouseLast();
        modes = {false, false, false, true};
        useAxis = {true, true, true};
    }
}

void OpenGL_Program::handleTextureModes(int key) {
    if(key==GLFW_KEY_D){
        modelObjects[selected].setUseTextures('d');
    }
    if(key==GLFW_KEY_A){
        modelObjects[selected].setUseTextures('a');
    }
    if(key==GLFW_KEY_S){
        modelObjects[selected].setUseTextures('s');
    }
    if(key==GLFW_KEY_N){
        modelObjects[selected].setUseTextures('n');
    }
}

void OpenGL_Program::handleTransformationMode(int key) {
    if (key == GLFW_KEY_X) {
        if (activeKeys[GLFW_KEY_RIGHT_SHIFT] || activeKeys[GLFW_KEY_LEFT_SHIFT]) {
            useAxis = {false, true, true};
            //cout<<"locking to y,z"<<endl;
        } else {
            useAxis = {true, false, false};
            //cout<<"locking to x"<<endl;
        }
    } else if (key == GLFW_KEY_Y) {
        if (activeKeys[GLFW_KEY_RIGHT_SHIFT] || activeKeys[GLFW_KEY_LEFT_SHIFT]) {
            useAxis = {true, false, true};
        } else {
            useAxis = {false, true, false};
        }
    } else if (key == GLFW_KEY_Z) {
        if (activeKeys[GLFW_KEY_RIGHT_SHIFT] || activeKeys[GLFW_KEY_LEFT_SHIFT]) {
            useAxis = {true, true, false};
        } else {
            useAxis = {false, false, true};
        }
    } else if (key == GLFW_KEY_A) {
        useAxis = {true, true, true};
    } else if (key == GLFW_KEY_W) {
        worldAxis = !worldAxis;
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
    if(modes.fps){
        //Move the camera using the mouse
        mouse.setMouseCurrent();
        camera.rotateView(mouse.getMouseDifference(mouse.getMouseCurrent(),mouse.getMouseLast()));
        glfwSetCursorPos(window,*window_width/2,*window_height/2);
        mouse.setMouseLast();
    }
    if(modes.scale){
        mouse.setMouseCurrent();
        mouse.teleportMouse(xpos,ypos);
        transformations.scale({useAxis.x,useAxis.y,useAxis.z},mouse);
        //modelObjects[0].setTempTransform();
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(modes.rotate){
        mouse.setMouseCurrent();
        mouse.teleportMouse(xpos,ypos);
        transformations.rotate({useAxis.x,useAxis.y,useAxis.z},mouse);
        //modelObjects[0].setTempTransform();
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(modes.move){
        mouse.setMouseCurrent();
        mouse.teleportMouse(xpos,ypos);
        transformations.translate({useAxis.x,useAxis.y,useAxis.z},mouse);
        //modelObjects[0].setTempTransform();
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
}

void OpenGL_Program::endCurrentMode() {
    modelObjects[selected].finalizeModelingTransformation(worldAxis);
    modes={false,false,false,false};
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void OpenGL_Program::commandLineArgs(vector<string> commandlineContents) {
    bool isConfigFile = false;
    if(commandlineContents[0].substr(commandlineContents[0].find_last_of('.') + 1) == "txt") {
        parseConfigFile(commandlineContents[0]);
    } else {
        Model model;
        model.addModel(commandlineContents[0]);
        for (int i = 1; i < (commandlineContents.size()); i+=2) {
            model.addTexture(commandlineContents[i][0], commandlineContents[i+1]);
        }
        modelObjects.push_back(model);
    }
}

void OpenGL_Program::parseConfigFile(string filename) {
    ifstream file;
    file.open( filename, fstream::in );
    if ( file.fail() ) {
        cout << "ERROR: Couldn't load \""
             << filename << "\"." << endl;
    }
    string line;
    int counter = -1;
    while(getline(file,line)){
        //cout<<line<<endl;
        //Create model and add it to model objects
        if(line.substr(0,4)=="####"){
            Model model;
            modelObjects.push_back(model);
            counter++;
        }
        //give a model its mesh data:
        if(line.substr(0,4)==">M: "){
            //model = Model();
            modelObjects[counter].addModel(line.substr(4, line.size()-1));
        }
        //give a model it's texture data:
        if(line.substr(0,4)==" D: "){
            modelObjects[counter].addTexture('d',line.substr(4, line.size()-1));
        }
        if(line.substr(0,4)==" A: "){
            modelObjects[counter].addTexture('a',line.substr(4, line.size()-1));
        }
        if(line.substr(0,4)==" S: "){
            modelObjects[counter].addTexture('s',line.substr(4, line.size()-1));
        }
    }
}
