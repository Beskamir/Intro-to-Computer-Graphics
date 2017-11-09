//
// main function heavily based on: https://learnopengl.com/code_viewer.php?code=getting-started/shaders-using-object
//

#include "main.h"
#include "setup.h"

int main(int argc, char *argv[]) {
    // initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
        return -1;
    }
    setWindowHints();
    if (!setupWindow()){
        return -1;
    }
    setWindowCallbacks();
// Initialize GLEW if on windows only
#ifdef _WIN32
    if (!initGLEW()){
        return -1;
    }
#endif
    //Call the mainRender method which actually sets up the verts to be drawn
    mainRender();
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glBindTexture(GL_TEXTURE_2D, 0);
    glfwDestroyWindow(window);
    glfwTerminate();
    cout << "Closing program" << endl;
    return 0;
}

void mainRender(){
    // Define the viewport dimensions
    glViewport(0, 0, window_width, window_height);

    // Build and compile the shader programs
    Shader mShaders("shaderData/vertex.glsl", "shaderData/fragment.glsl");

    GLuint mTexture=0;
    int imageWidth=0, imageHeight=0;
    loadImage(&mTexture,&imageWidth,&imageHeight);
    // Set up vertex shaderData (and buffer(s)) and attribute pointers
    Mesh imagePlane=genImagePlane(imageWidth,imageHeight);

    glBindTexture(GL_TEXTURE_2D, mTexture);
    vertexArray verts(imagePlane.vertices.size()/3);
    verts.addBuffer("v", 0, imagePlane.vertices);
    verts.addBuffer("c", 1, imagePlane.colors);
    verts.addBuffer("t", 2, imagePlane.texture);

    // main render loop, keeps running until window is closed
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        //Render to screen loop
        renderToScreen(mShaders, verts);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
}


void renderToScreen(Shader mShaders, vertexArray &verts) {
    // clear screen to a dark grey colour
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    mShaders.Use();

    setupTransformations(mShaders);
    setImageStyle(mShaders);
    setControlPoints(mShaders,0);

    drawImage(verts);

    setControlPoints(mShaders,1);
    drawPoints();

    glUseProgram(0);
}



void drawPoints() {
    if(!controlPoints.vertices.empty()){
        vertexArray cPoints(controlPoints.vertices.size()/3);
        cPoints.addBuffer("v", 0, controlPoints.vertices);
        cPoints.addBuffer("c", 1, controlPoints.colors);
        cPoints.addBuffer("t", 2, controlPoints.texture);
        glBindVertexArray(cPoints.id);
        glDrawArrays(GL_POINTS, 0, cPoints.count);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glBindVertexArray(0);
        //cout <<"should be drawing a point"<<endl;
    }
}

void drawImage(vertexArray &verts) {
    glBindVertexArray(verts.id);
    glDrawArrays(GL_TRIANGLES, 0, verts.count);
    glBindVertexArray(0);
}

void setControlPoints(Shader mShaders, int isControlPoint) {
    GLint imageStyleLocation = glGetUniformLocation(mShaders.Program, "controlPoints");
    glUniform1i(imageStyleLocation,isControlPoint);
}

void setImageStyle(Shader mShaders) {
    GLint imageStyleLocation = glGetUniformLocation(mShaders.Program, "imageStyle");
    glUniform1i(imageStyleLocation,imageStyle);
}

void setupTransformations(Shader mShaders) {
    //Create transformations
    glm::mat4 transformFunction;
    transformFunction = glm::scale(transformFunction, glm::vec3(scaleFactor, scaleFactor, 1.0f));
    transformFunction = glm::translate(transformFunction, glm::vec3(translate.x, translate.y, 0.0f));
    // Get matrix's uniform location and set matrix
    GLint transformationLocation = glGetUniformLocation(mShaders.Program, "transformation");
    glUniformMatrix4fv(transformationLocation, 1, GL_FALSE, glm::value_ptr(transformFunction));
}

void addControlPoint() {
    Position mouseLocation=getMouseLocation();
    //Fix the location where points should be drawn if the image has been moved or scaled
    glm::mat4 correctiveTransform;
    correctiveTransform = glm::translate(correctiveTransform, glm::vec3(-translate.x, -translate.y, 0.0f));
    correctiveTransform = glm::scale(correctiveTransform, glm::vec3(1/scaleFactor, 1/scaleFactor, 1.0f));

    glm::vec4 fixedLocation={mouseLocation.x,mouseLocation.y,1,1};
    fixedLocation = correctiveTransform * fixedLocation;


    vector<float> pointVerts={fixedLocation.x,fixedLocation.y,fixedLocation.z};
    vector<float> pointColor={0,0,0};
    //controlPoints.vertices={};
    for (int i = 0; i < pointColor.size(); ++i) {
        controlPoints.vertices.push_back(pointVerts[i]);
        controlPoints.colors.push_back(pointColor[i]);
        controlPoints.texture.push_back(0);
    }
}