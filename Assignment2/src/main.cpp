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
    glfwDestroyWindow(window);
    glfwTerminate();
    cout << "Closing program" << endl;
    return 0;
}

void mainRender(){
    // Define the viewport dimensions
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Build and compile the shader programs
    Shader mShaders("shaderData/vertex.glsl", "shaderData/fragment.glsl");

    //Bind texture
    GLuint mTexture;
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);

    //Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);

    int imageWidth, imageHeight, imageLayers;
    string filename="imageData/texture.jpg";
    //string filename="imageData/widerImage.jpg";
    //string filename="imageData/tallerImage.jpg";
    unsigned char* image = stbi_load(filename.c_str(), &imageWidth, &imageHeight, &imageLayers, STBI_rgb);

    if(image == nullptr){
        printf("Failed to load texture\n");
        exit(-1);
    }

    //printf("checking layers: %d:%d\n",imageWidth,imageHeight);

    if(imageLayers == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    else if(imageLayers == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    else{
        printf("Texture not rgb or rgba\n");
        exit(-1);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    //glActiveTexture(GL_TEXTURE0);
    //glUniform1i(glGetUniformLocation(mShaders.Program, "texture1"), 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);

    // Set up vertex shaderData (and buffer(s)) and attribute pointers
    Mesh imagePlane=genImagePlane(imageWidth,imageHeight);

    glBindTexture(GL_TEXTURE_2D, mTexture);
    vertexArray verts((int)imagePlane.vertices.size()/3);
    verts.addBuffer("v", 0, imagePlane.vertices);
    verts.addBuffer("c", 1, imagePlane.colors);
    verts.addBuffer("t", 2, imagePlane.texture);

    //Create transformations
    glm::mat4 transformFunction;
    transformFunction = glm::scale(transformFunction, glm::vec3(5.0f, 5.0f, 1.0f));
    //transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    // Get matrix's uniform location and set matrix
    GLint transformationLocation = glGetUniformLocation(mShaders.Program, "transformation");
    glUniformMatrix4fv(transformationLocation, 1, GL_FALSE, glm::value_ptr(transformFunction));

    //glUniformMatrix4fv()

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        renderToScreen(mShaders, verts);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
}

void renderToScreen(Shader mShaders, vertexArray &verts) {
    // clear screen to a dark grey colour
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    mShaders.Use();
    glBindVertexArray(verts.id);
    glDrawArrays(GL_TRIANGLES, 0, verts.count);
    glBindVertexArray(0);

    //glUseProgram(program.id);
    //glBindVertexArray(va.id);
    //glDrawArrays(drawingMode, 0, va.count);

    //glBindVertexArray(0);
    glUseProgram(0);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS){

    }

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

///Get mesh for the image
Mesh genImagePlane(int imageWidth, int imageHeight) {
    Mesh imagePlane;
    double scaleHeight, scaleWidth;

    if(imageWidth>imageHeight){
        scaleHeight=(double)imageHeight/imageWidth;
        scaleWidth=(double)imageWidth/imageWidth;
    }
    else if(imageWidth<imageHeight){
        scaleHeight=(double)imageHeight/imageHeight;
        scaleWidth=(double)imageWidth/imageHeight;
    }
    else{
        scaleHeight=1;
        scaleWidth=1;
    }
    //cout<<scaleHeight<<":"<<scaleWidth<<endl;

    vector<vector<float>> verticies = {{1.0f,  1.0f, 0.0f},
                                       {1.0f, -1.0f, 0.0f},
                                       {-1.0f, -1.0f, 0.0f},
                                       {-1.0f,  1.0f, 0.0f},};
    for (int i = 0; i < verticies.size(); ++i) {
        verticies[i][0]*=scaleWidth;
        verticies[i][1]*=scaleHeight;
    }
    vector<vector<float>> colors = {{1.0f, 0.0f, 0.0f},
                                    {0.0f, 1.0f, 0.0f},
                                    {0.0f, 0.0f, 1.0f},
                                    {1.0f, 1.0f, 0.0f},};
    vector<vector<float>> uvCoords = {{1.0f, 1.0f},
                                      {1.0f, 0.0f},
                                      {0.0f, 0.0f},
                                      {0.0f, 1.0f},};
    //To scale texture scale the verts and redraw
    //for (int i = 0; i < verticies.size(); ++i) {
    //    int scale = 7;
    //    verticies[i][0]*=scale;
    //    verticies[i][1]*=scale;
    //}
    imagePlane.vertices={};
    imagePlane.colors={};
    imagePlane.texture={};
    //Create a square using two triangles and the above defined points
    for (int k = 0; k < 2; ++k) {
        for (int j = 0; j < verticies.size(); ++j) {
            if(k==0 && j!=2){
                imagePlane.vertices.insert(imagePlane.vertices.end(),verticies[j].begin(),verticies[j].end());
                imagePlane.colors.insert(imagePlane.colors.end(),colors[j].begin(),colors[j].end());
                imagePlane.texture.insert(imagePlane.texture.end(),uvCoords[j].begin(),uvCoords[j].end());
            }
            else if(k==1&&j!=0){
                imagePlane.vertices.insert(imagePlane.vertices.end(),verticies[j].begin(),verticies[j].end());
                imagePlane.colors.insert(imagePlane.colors.end(),colors[j].begin(),colors[j].end());
                imagePlane.texture.insert(imagePlane.texture.end(),uvCoords[j].begin(),uvCoords[j].end());
            }
        }
    }
    return imagePlane;
}
