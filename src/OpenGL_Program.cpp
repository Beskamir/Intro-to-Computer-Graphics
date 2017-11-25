//
// Main OpenGL Program, does all the input handling and setup of the models
//

#include "OpenGL_Program.h"

void OpenGL_Program::mainRender(){
    // Define the viewport dimensions
    glViewport(0, 0, *window_width, *window_height);
    mouse = Mouse(window, window_width, window_height);
    placeCameraConsideringAllModels();

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

        if(!(modes.fps||keyboardNumericInput[currentAxis].empty())){
            keyboardTransformations();
        }
        if(modes.move){
            moveModelUsingKeyboard();
        }

        //Render to screen loop
        renderToScreen(modelObjects);
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
}

void OpenGL_Program::renderToScreen(vector<Model> modelObjects) {
    // clear screen to a dark grey colour
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
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
        transformations.clear();
        keyboardNumericInput[currentAxis] = "";
        modelObjects[selected].clearTempTransformations();
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
        if(key == GLFW_KEY_C){
            camera.centerView(modelObjects[selected]);
        }
        handleNonFPS_Mode(key);
    }
}

void OpenGL_Program::handleNonFPS_Mode(int key) {
    if(key==GLFW_KEY_D&&(activeKeys[GLFW_KEY_LEFT_SHIFT]||activeKeys[GLFW_KEY_RIGHT_SHIFT])){
        keyboardNumericInput[currentAxis]="";
        transformations.clear();
        mouse.reset();
        mouse.setMouseLast();
        modes = {false, false, false, true};
        useAxis = {true, true, true};
        modelObjects.push_back(modelObjects[selected]);
        selected = modelObjects.size()-1;
    }
    if (modes.rotate || modes.scale || modes.move) {
        handleTransformationMode(key);
        tryActivatingTransformations(key);
        tryUsingNumericKeyInput(key);
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
        keyboardNumericInput[currentAxis]="";
        transformations.clear();
        mouse.reset();
        mouse.setMouseLast();
        modes = {false, true, false, false};
        useAxis = {true, true, true};
    }
    if (key == GLFW_KEY_R && !modes.rotate) {
        keyboardNumericInput[currentAxis]="";
        transformations.clear();
        mouse.reset();
        mouse.setMouseLast();
        modes = {false, false, true, false};
        useAxis = {true, true, true};
    }
    if (key == GLFW_KEY_G && !modes.move) {
        keyboardNumericInput[currentAxis]="";
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
            axisSelected = {true,false,false};
            useAxis = {true, false, false};
            //cout<<"locking to x"<<endl;
        }
        if(activeKeys[GLFW_KEY_RIGHT_CONTROL]||activeKeys[GLFW_KEY_LEFT_CONTROL]){
            axisSelected = {true, false, false};
        }
        keyboardNumericInput[0] = "";
    } else if (key == GLFW_KEY_Y) {
        if (activeKeys[GLFW_KEY_RIGHT_SHIFT] || activeKeys[GLFW_KEY_LEFT_SHIFT]) {
            useAxis = {true, false, true};
        } else {
            axisSelected = {false,true,false};
            useAxis = {false, true, false};
        }
        if(activeKeys[GLFW_KEY_RIGHT_CONTROL]||activeKeys[GLFW_KEY_LEFT_CONTROL]){
            axisSelected = {false, true, false};
        }
        keyboardNumericInput[1] = "";
    } else if (key == GLFW_KEY_Z) {
        if (activeKeys[GLFW_KEY_RIGHT_SHIFT] || activeKeys[GLFW_KEY_LEFT_SHIFT]) {
            useAxis = {true, true, false};
        } else {
            axisSelected = {false,false,true};
            useAxis = {false, false, true};
        }
        if(activeKeys[GLFW_KEY_RIGHT_CONTROL]||activeKeys[GLFW_KEY_LEFT_CONTROL]){
            axisSelected = {false, false, true};
        }
        keyboardNumericInput[2] = "";
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
        camera.moveCamera({activeKeys[GLFW_KEY_W],activeKeys[GLFW_KEY_S],activeKeys[GLFW_KEY_D],activeKeys[GLFW_KEY_A],activeKeys[GLFW_KEY_E],activeKeys[GLFW_KEY_Q]}, (float) deltaTime);
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
        axisSelected = {true,false,false};
        mouse.setMouseCurrent();
        mouse.teleportMouse(xpos,ypos);
        transformations.scale(useAxis,mouse);
        //modelObjects[0].setTempTransform();
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(modes.rotate){
        axisSelected = {true,false,false};
        mouse.setMouseCurrent();
        mouse.teleportMouse(xpos,ypos);
        transformations.rotate(useAxis,mouse);
        //modelObjects[0].setTempTransform();
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(modes.move && !(activeKeys[GLFW_KEY_U]||activeKeys[GLFW_KEY_I]||activeKeys[GLFW_KEY_O]||activeKeys[GLFW_KEY_J]||activeKeys[GLFW_KEY_K]||activeKeys[GLFW_KEY_L])){
        vec2 mouseLocation = mouse.getMouseScreenLoc();
        GLfloat depth=0.5f;

        //vec3 projectedMousePos = getProjectedMousePosition();
        vec4 viewport = vec4(0, 0, *window_width, *window_height);
        vec3 windowCoordinates = vec3(mouseLocation.x, *window_height - mouseLocation.y - 1, depth);
        vec3 sceneCoordinates = unProject(windowCoordinates, camera.getView(), camera.getProjection(), viewport);


        axisSelected = {true,false,false};
        mouse.setMouseCurrent();
        mouse.teleportMouse(xpos,ypos);
        transformations.translate(useAxis,modelObjects[selected].getOrigin(),sceneCoordinates);
        //modelObjects[0].setTempTransform();
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
}

void OpenGL_Program::endCurrentMode() {
    modelObjects[selected].finalizeModelingTransformation(worldAxis);
    modes={false,false,false,false};
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void OpenGL_Program::handleMouseClick() {
    if(modes.move||modes.fps||modes.rotate||modes.scale){
        endCurrentMode();
    }
    else{
        selectObject();
    }

}

void OpenGL_Program::commandLineArgs(vector<string> commandlineContents) {
    if(commandlineContents[0].substr(commandlineContents[0].find_last_of('.') + 1) == "txt") {
        //cout<<"parsing file"<<endl;
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

void OpenGL_Program::tryUsingNumericKeyInput(int key) {
    //string previous="";
    //for (int i = 0; i < keyboardNumericInput->length(); ++i) {
    //    previous = keyboardNumericInput[i];
    //}
    getNumericKeyInput(key); //if key pressed is valid store in string

    fixStringErrors();

    //transformUsingNumericValues()
    //double numericKeyboardInput = atof(tempKeyboardNumericInput.c_str());
    //cout<<key<<endl;
}

void OpenGL_Program::keyboardTransformations() {
    if(modes.scale){
        transformations.scale(useAxis,transform.x);
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(modes.rotate){
        transformations.rotate(useAxis,transform.x);
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(modes.move){
        transformations.translate(useAxis,transform);
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
}

void OpenGL_Program::getNumericKeyInput(int key) {
    if(key==GLFW_KEY_MINUS){
        //Negate value
        if(keyboardNumericInput[currentAxis].substr(0,1)=="-"){
            keyboardNumericInput[currentAxis]=keyboardNumericInput[currentAxis].substr(1,keyboardNumericInput[currentAxis].size()-1);
        }else{
            keyboardNumericInput[currentAxis]="-"+keyboardNumericInput[currentAxis];
        }
    }
    if(key==GLFW_KEY_PERIOD){
        if(keyboardNumericInput[currentAxis].empty()){
            keyboardNumericInput[currentAxis] += '.';
        } else{
            bool foundDot = false;
                if(keyboardNumericInput[currentAxis].find('0')=='.'){
                    foundDot= true;
                }
            if(!foundDot){
                keyboardNumericInput[currentAxis] += '.';
            }
        }
    }
    if(key>=48&&key<=57){
        keyboardNumericInput[currentAxis] += key;
    }
}

void OpenGL_Program::fixStringErrors() {
//fix probable errors in string
    string tempKeyboardNumericInput = keyboardNumericInput[currentAxis];
    if(!keyboardNumericInput[currentAxis].empty()){
        if(tempKeyboardNumericInput.substr(0,1)=="."){
            tempKeyboardNumericInput = "0"+tempKeyboardNumericInput;
        }
        if(tempKeyboardNumericInput.substr(tempKeyboardNumericInput.length()-1,tempKeyboardNumericInput.length())=="."){
            tempKeyboardNumericInput += "0";
        }
    }
    //vec3 tempTransform=transform;
    //sscanf(tempKeyboardNumericInput.c_str(),"%f,%f,%f",&transform.x,&transform.y,&transform.z);

    //cout<<"\nUnprocessed keyboard input: \n\t"<<keyboardNumericInput<<endl;
    //cout<<"Processed keyboard input: \n\t";

    if(axisSelected.x){
        //cout << "<X>:[";
        if(useAxis.x){
            sscanf(tempKeyboardNumericInput.c_str(),"%f",&transform.x);
        }
        else{
            transform.x=0;
        }
    }
    else{
        //cout << "x:[";
    }
    //cout << transform.x << "]";
    if(axisSelected.y){
        //cout << "<Y>:[";
        if(useAxis.y){
            sscanf(tempKeyboardNumericInput.c_str(),"%f",&transform.y);
        }
        else{
            transform.y=0;
        }
    }
    else{
        //cout << "y:[";
    }
    //cout << transform.y << "]";
    //cout << "y:[" << transform.y << "]";
    if(axisSelected.z){
        //cout << "<Z>:[";
        if(useAxis.z){
            sscanf(tempKeyboardNumericInput.c_str(),"%f",&transform.z);
        }
        else{
            transform.z=0;
        }
    }
    else{
        //cout << "z:[";
    }
    //cout << transform.z << "]\n";
    //cout << "z:[" << transform.z << "]\n\n" << endl;
}

//Select object function heavily based on: https://en.wikibooks.org/wiki/OpenGL_Programming/Object_selection
void OpenGL_Program::selectObject() {

    vec3 sceneCoordinates = getProjectedMousePosition();
    vec2 closest = vec2(-1,-1);

    for (int i = 0; i < modelObjects.size(); ++i) {
        if (closest.y < 0) {
            closest = vec2(getDistance(modelObjects[i].getOrigin(), sceneCoordinates), i);
        } else if (closest.x > getDistance(modelObjects[i].getOrigin(), sceneCoordinates)) {
            closest = vec2(getDistance(modelObjects[i].getOrigin(), sceneCoordinates), i);
        }
    }
    //cout << closest.x<<":"<<closest.y<<endl;
    selected = (int) closest.y; //set which model is active/selected

    //printf("Coordinates in object space: %f, %f, %f\n",
    //       sceneCoordinates.x, sceneCoordinates.y, sceneCoordinates.z);
}

//Way too tired to figure this out right now, taking the function from here: https://www.opengl.org/discussion_boards/showthread.php/175295-glm-vector-distanceSquare
float OpenGL_Program::getDistance(vec3 coord1, vec3 coord2) {
    vec3 temp = coord1 - coord2;
    return dot(temp, temp);
}

vec3 OpenGL_Program::getProjectedMousePosition() {
    vec2 mouseLocation = mouse.getMouseScreenLoc();
    GLbyte color[4];
    GLfloat depth;
    //GLuint index;

    glReadPixels((GLuint) mouseLocation.x, *window_height - (GLuint) mouseLocation.y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels((GLuint) mouseLocation.x, *window_height - (GLuint) mouseLocation.y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    //glReadPixels((GLuint) mouseLocation.x, *window_height - (GLuint) mouseLocation.y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    //printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
    //       (GLuint) mouseLocation.x, (GLuint) mouseLocation.y, color[0], color[1], color[2], color[3], depth, index);

    vec4 viewport = vec4(0, 0, *window_width, *window_height);
    vec3 windowCoordinates = vec3(mouseLocation.x, *window_height - mouseLocation.y - 1, depth);
    vec3 sceneCoordinates = unProject(windowCoordinates, camera.getView(), camera.getProjection(), viewport);

    return sceneCoordinates;
}

void OpenGL_Program::placeCameraConsideringAllModels() {
    float xCoord[2]={0,0};
    float yCoord[2]={0,0};
    float zCoord[2]={0,0};
    for (int i = 0; i < modelObjects.size(); ++i) {
        if(modelObjects[i].boundingBox.xCoord[0]>xCoord[0]){
            xCoord[0]=modelObjects[i].boundingBox.xCoord[0];
        }
        if(modelObjects[i].boundingBox.xCoord[1]>xCoord[1]){
            xCoord[1]=modelObjects[i].boundingBox.xCoord[1];
        }
        if(modelObjects[i].boundingBox.yCoord[0]>yCoord[0]){
            yCoord[0]=modelObjects[i].boundingBox.yCoord[0];
        }
        if(modelObjects[i].boundingBox.yCoord[1]>yCoord[1]){
            yCoord[1]=modelObjects[i].boundingBox.yCoord[1];
        }
        if(modelObjects[i].boundingBox.zCoord[0]>zCoord[0]){
            zCoord[0]=modelObjects[i].boundingBox.zCoord[0];
        }
        if(modelObjects[i].boundingBox.zCoord[1]>zCoord[1]){
            zCoord[1]=modelObjects[i].boundingBox.zCoord[1];
        }
    }

    camera.initalCameraLocation(modelObjects[selected],xCoord,yCoord,zCoord);
}

void OpenGL_Program::moveModelUsingKeyboard() {
    float transformRate = 0.05f;
    if(activeKeys[GLFW_KEY_U]){
        transform.y+=transformRate;
        transformations.translate(useAxis,transform);
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(activeKeys[GLFW_KEY_O]){
        transform.y-=transformRate;
        transformations.translate(useAxis,transform);
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(activeKeys[GLFW_KEY_I]){
        transform.z+=transformRate;
        transformations.translate(useAxis,transform);
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(activeKeys[GLFW_KEY_K]){
        transform.z-=transformRate;
        transformations.translate(useAxis,transform);
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(activeKeys[GLFW_KEY_J]){
        transform.x-=transformRate;
        transformations.translate(useAxis,transform);
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    if(activeKeys[GLFW_KEY_L]){
        transform.x+=transformRate;
        transformations.translate(useAxis,transform);
        modelObjects[selected].setTempTransform(transformations.getTransformation());
    }
    //modelObjects[0].setTempTransform();
    //    if(modes.fps){
    //        //Pass along {W,S,D,A} == {forward, backward, right, left}
    //        camera.moveCamera({activeKeys[GLFW_KEY_W],activeKeys[GLFW_KEY_S],activeKeys[GLFW_KEY_D],activeKeys[GLFW_KEY_A],activeKeys[GLFW_KEY_E],activeKeys[GLFW_KEY_Q]}, (float) deltaTime);
    //    }
}