//
// Created by Sebastian on 11/13/2017.
//

#include "OpenGL_Program.h"

void OpenGL_Program::mainRender(){
    // Define the viewport dimensions
    glViewport(0, 0, *window_width, *window_height);
    vector<Model> modelObjects;

    //forloop to open all the models and textures
    Model model = Model("data/models/sphereTest.obj");
    //Model model = Model("data/models/pyramidTest.obj");
    //Model model = Model("data/models/offical/chess_king/king.obj");
    model.addTexture("data/imageData/Tower.png");
    //model.genImagePlane();

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
    glClear(GL_COLOR_BUFFER_BIT);

    mShaders.bind();
    for (int i = 0; i < modelObjects.size(); ++i) {
        setupTransformations(mShaders,i); //set transformations
        modelObjects[i].drawModel();
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
