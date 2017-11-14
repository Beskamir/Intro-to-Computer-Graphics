//
// Created by Sebastian on 11/13/2017.
//

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void Texture::addTexture(GLuint *mTexture, int *imageWidth, int *imageHeight) {
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
