//
// Created by Sebastian on 11/13/2017.
//

#include "OpenGL_Program.h"

void OpenGL_Program::mainRender(){
    // Define the viewport dimensions
    glViewport(0, 0, *window_width, *window_height);
    vector<Model> modelObjects;

    //forloop to open all the models and textures
    //Model model = Model("data/models/sphereTest.obj");
    //Model model = Model("data/models/pyramidTest.obj");
    Model model = Model("data/models/offical/chess_king/king.obj");
    model.addTexture("data/imageData/Tower.png");
    //model.genImagePlane();
    //model.getFurthestPoints();
    initalCameraLocation(model);

    modelObjects.push_back(model);
    //loadImage(&mTexture,&imageWidth,&imageHeight);
    // Set up vertex shaderData (and buffer(s)) and attribute pointers
    //Mesh imagePlane=genImagePlane(imageWidth,imageHeight);
//    Mesh imagePlane=genImagePlane(1000,1000);
//    model.meshData.vertices;
//    vertexArray verts = model.use();

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
        setupTransformations(mShaders,i); //set transformations
        modelObjects[i].drawModel(modelLoc);
        //drawModel(modelObjects[i]); //draw the object
        //setTextureUsage(1);
    }
    glUseProgram(0); //cleanup
    //Set image style and whether using a texture or vertex colors
    //setImageStyle();
    //setTextureUsage(1);
}


void OpenGL_Program::drawModel(Model model) {
    //glBindVertexArray(verts.id);
    //glDrawElements(GL_TRIANGLES,verts.count,GL_UNSIGNED_INT,0);
    ////glDrawArrays(GL_TRIANGLES, 0, verts.count);
    //glBindVertexArray(0);
}

//void OpenGL_Program::setTextureUsage(int textureUsage) {
//    GLint imageStyleLocation = glGetUniformLocation(mShaders.id, "useTexture");
//    glUniform1i(imageStyleLocation,textureUsage);
//}

void OpenGL_Program::setupTransformations(ShaderProgram shaderProgram, int i) {
    //Create transformations
    glm::mat4 transformFunction;
    //transformFunction = glm::scale(transformFunction, glm::vec3(scaleFactor, scaleFactor, 1.0f));
    //transformFunction = glm::translate(transformFunction, glm::vec3(translate.x, translate.y, 0.0f));
    // Get matrix's uniform location and set matrix
    GLint transformationLocation = glGetUniformLocation(shaderProgram.id, "transformation");
    glUniformMatrix4fv(transformationLocation, 1, GL_FALSE, glm::value_ptr(transformFunction));
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

void OpenGL_Program::moveCamera(int key) {
    if(key == GLFW_KEY_W){
        cameraPosition += cameraSpeed * cameraFront;
    }
    if(key == GLFW_KEY_S){
        cameraPosition -= cameraSpeed * cameraFront;
    }
    if(key == GLFW_KEY_A){
        cameraPosition -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if(key == GLFW_KEY_D){
        cameraPosition += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
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
    cout<< xOffset<<":"<<yOffset<<endl;
    GLfloat sensitivity = 25;	// Change this value to your liking
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw   += xOffset;
    pitch += yOffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(radians(yaw)) * cos(radians(pitch));
    front.y = sin(radians(pitch));
    front.z = sin(radians(yaw)) * cos(radians(pitch));
    cameraFront = normalize(front);
}
