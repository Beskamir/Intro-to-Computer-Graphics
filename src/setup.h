//
// Setup functions to help the main function set things up.
// Ideally will make things cleaner in the main function
//

#ifndef ASSIGNMENT2_SETUP_H
#define ASSIGNMENT2_SETUP_H

#include "inputHandler.h"

void loadImage(GLuint *mTexture, int *imageWidth, int *imageHeight) {
    //loadImage(&mTexture,&imageWidth,&imageHeight);
    int imageLayers;
    //Bind texture
    glGenTextures(1, mTexture);
    glBindTexture(GL_TEXTURE_2D, *mTexture);

    //Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_WRAP_BORDER);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_WRAP_BORDER);

//    string filename="data/imageData/texture.jpg";
//    string filename="data/imageData/widerImage.jpg";
//    string filename="data/imageData/tallerImage.jpg";
//    string filename="data/imageData/Nihilus.jpg";
//    string filename="data/imageData/GeraltAndCiri.jpg";
//    string filename="data/imageData/CaliforniaCondor.jpg";
    string filename="data/imageData/Tower.png";
//    cout<<filename.c_str()<<endl;
    unsigned char* image = stbi_load(filename.c_str(), imageWidth, imageHeight, &imageLayers, STBI_rgb);

    if(image == nullptr){
        printf("Failed to load texture\n");
//        return;
        exit(-1);
    }

    //printf("checking layers: %d:%d\n",imageWidth,imageHeight);

    if(imageLayers == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *imageWidth, *imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    else if(imageLayers == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *imageWidth, *imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    else{
        printf("Texture not rgb or rgba\n");
        return;
//        exit(-1);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    //glActiveTexture(GL_TEXTURE0);
    //glUniform1i(glGetUniformLocation(mShaders.Program, "texture1"), 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);
}
// Initialize GLEW if on windows only
#ifdef _WIN32
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
#endif


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

    //Create a square using two triangles and the above defined points
    imagePlane.vertices = {verticies[0],
                           verticies[1],
                           verticies[3],

                           verticies[1],
                           verticies[2],
                           verticies[3],
    };
    imagePlane.colors={colors[0],
                       colors[1],
                       colors[3],

                       colors[1],
                       colors[2],
                       colors[3],
    };
    imagePlane.texture={uvCoords[0],
                        uvCoords[1],
                        uvCoords[3],

                        uvCoords[1],
                        uvCoords[2],
                        uvCoords[3],
    };
    return imagePlane;
}

#endif //ASSIGNMENT2_SETUP_H
