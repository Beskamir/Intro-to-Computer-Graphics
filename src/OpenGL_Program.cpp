//
// Created by Sebastian on 11/13/2017.
//

#include "OpenGL_Program.h"

void OpenGL_Program::mainRender(){
    // Define the viewport dimensions
    glViewport(0, 0, *window_width, *window_height);

    Model model = Model();
    model.addTexture();
    model.genImagePlane();

    //loadImage(&mTexture,&imageWidth,&imageHeight);
    // Set up vertex shaderData (and buffer(s)) and attribute pointers
    //Mesh imagePlane=genImagePlane(imageWidth,imageHeight);
//    Mesh imagePlane=genImagePlane(1000,1000);
    model.meshData.vertices;
    vertexArray verts = model.use();


    // main render loop, keeps running until window is closed
    while (!glfwWindowShouldClose(window)){
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        //Render to screen loop
        renderToScreen(verts);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
}


void OpenGL_Program::renderToScreen(vertexArray &verts) {
    // clear screen to a dark grey colour
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    mShaders.bind();
    //Setup the transformations that will be used to move the image, curves, points, etc.
    setupTransformations(mShaders);

    //Set image style and whether using a texture or vertex colors
    //setImageStyle();
    setTextureUsage(1);
    drawImage(verts); //Draw the image
    glUseProgram(0);

    //Draw Lines
    lineShader.bind();
    setupTransformations(lineShader);
    setTextureUsage(2);
    //drawCurves();
    glUseProgram(0);

    mShaders.bind();
    //Draw Control Points
    //if(showControlPoints){
    //    setTextureUsage(0);
    //    //drawPoints();
    //}

    glUseProgram(0);
}


void OpenGL_Program::drawImage(vertexArray &verts) {
    glBindVertexArray(verts.id);
    glDrawArrays(GL_TRIANGLES, 0, verts.count);
    glBindVertexArray(0);
}

void OpenGL_Program::setTextureUsage(int textureUsage) {
    GLint imageStyleLocation = glGetUniformLocation(mShaders.id, "useTexture");
    glUniform1i(imageStyleLocation,textureUsage);
}

void OpenGL_Program::setupTransformations(ShaderProgram shaderProgram) {
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
    //mShaders.attachShader("shaderData/vertex.glsl", GL_VERTEX_SHADER);
    //mShaders.attachShader("shaderData/fragment.glsl", GL_FRAGMENT_SHADER);
    //mShaders.link();


    if (!lineShader.attachShader("data/shaderData/lineVert.glsl", GL_VERTEX_SHADER))
        cout << "Error attaching vertex shader"<<endl;
    if (!lineShader.attachShader("data/shaderData/geometry.glsl",GL_GEOMETRY_SHADER))
        cout << "Error attaching geometry shader"<<endl;
    if (!lineShader.attachShader("data/shaderData/lineFrag.glsl", GL_FRAGMENT_SHADER))
        cout << "Error attaching fragment shader"<<endl;
    if (!lineShader.link())
        cout<<"Error linking shader program"<<endl;
}
