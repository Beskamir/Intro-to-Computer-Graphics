//
// Setup functions to help the main function set things up.
// Ideally will make things cleaner in the main function
//

#ifndef ASSIGNMENT2_SETUP_H
#define ASSIGNMENT2_SETUP_H

#include "inputHandler.h"

//Setup glew
bool initGLEW() {
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        cout << "glew init failed" << endl;
        return false;
    }
    return true;
}

// Create a GLFWwindow object that we can use for GLFW's functions
bool setupWindow() {
    window = glfwCreateWindow(window_width, window_height, "CPSC 453 Assignment 2", nullptr, nullptr);

    //Check that window was properly setup
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    return true;
}

// Set options for GLFW such as telling it to use OpenGL 4.1
void setWindowHints() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Set the required callback functions
void setWindowCallbacks() {
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

void loadImage(GLuint *mTexture, int *imageWidth, int *imageHeight) {
    //loadImage(&mTexture,&imageWidth,&imageHeight);
    int imageLayers;
    //Bind texture
    glGenTextures(1, mTexture);
    glBindTexture(GL_TEXTURE_2D, *mTexture);

    //Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_WRAP_BORDER);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_WRAP_BORDER);

    //string filename="imageData/texture.jpg";
    //string filename="imageData/widerImage.jpg";
    //string filename="imageData/tallerImage.jpg";
    //string filename="imageData/Nihilus.jpg";
    //string filename="imageData/GeraltAndCiri.jpg";
    //string filename="imageData/CaliforniaCondor.jpg";
    string filename="imageData/Tower.png";
    unsigned char* image = stbi_load(filename.c_str(), imageWidth, imageHeight, &imageLayers, STBI_rgb);

    if(image == nullptr){
        printf("Failed to load texture\n");
        exit(-1);
    }

    //printf("checking layers: %d:%d\n",imageWidth,imageHeight);

    if(imageLayers == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *imageWidth, *imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    else if(imageLayers == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *imageWidth, *imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    else{
        printf("Texture not rgb or rgba\n");
        exit(-1);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    //glActiveTexture(GL_TEXTURE0);
    //glUniform1i(glGetUniformLocation(mShaders.Program, "texture1"), 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);
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


#endif //ASSIGNMENT2_SETUP_H
