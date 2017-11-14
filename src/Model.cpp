//
// Created by Sebastian on 11/13/2017.
//

#include "Model.h"

Model::Model() {



}

Model::Model(string filepath) {



}

void Model::addTexture(){
    Texture texture;
    texture.addTexture(&mTexture,&imageWidth,&imageHeight);
}

void Model::genImagePlane(){
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
    meshData.vertices = {verticies[0],
                         verticies[1],
                         verticies[3],

                         verticies[1],
                         verticies[2],
                         verticies[3],
    };
    meshData.colors={colors[0],
                     colors[1],
                     colors[3],

                     colors[1],
                     colors[2],
                     colors[3],
    };
    meshData.uvCoords={uvCoords[0],
                       uvCoords[1],
                       uvCoords[3],

                       uvCoords[1],
                       uvCoords[2],
                       uvCoords[3],
    };
}

vertexArray Model::use() {

    glBindTexture(GL_TEXTURE_2D, mTexture);
    vertexArray verts(meshData.vertices.size()*meshData.vertices[0].size()/3);
    verts.addBuffer("v", 0, meshData.vertices);
    verts.addBuffer("c", 1, meshData.colors);
    verts.addBuffer("t", 2, meshData.uvCoords);

    return verts;
}
