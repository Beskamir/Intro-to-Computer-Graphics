//
// Created by Sebastian on 11/13/2017.
//

#include "Model.h"

//include STB for opening the texture
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model() {



}

Model::Model(string filepath) {
    openOBJ(filepath);
}

//Following function based on:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// https://stackoverflow.com/questions/21120699/c-obj-file-parser
void Model::openOBJ(string filename) {
    //char_separator<char> whitespace = char_separator<char>( " \t" );
    //char_separator<char> faceSeparator = char_separator<char>( "/" );
    vector<int> vertexIndices, uvIndices, normalIndices;
    vector<vec3> temp_vertices;
    vector<vec3> temp_normals;
    vector<vec2> temp_uvs;

    // try to open the file
    ifstream file;
    file.open( filename, fstream::in );
    // didn't work? fail!
    if ( file.fail() ) {
        cout << "ERROR: OBJmodel: Couldn't load \""
             << filename << "\"." << endl;
    }

    string line; // a buffer to store lines in, and separators
    const char* values;
    //Process the file
    while(getline(file,line)) {	// while we have data, read in a line

        if (line.substr(0,2)=="v "){
            vec3 vertex;
            values = line.c_str();
            sscanf(values, "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            //cout<<"V: "<<vertex.x<<" "<<vertex.y<<" "<<vertex.z<<endl;
            temp_vertices.push_back(vertex);
        }
            //Process uv coordinates at each vertex
        else if (line.substr(0,2)=="vt"){
            vec2 uv;
            values = line.c_str();
            sscanf(values, "vt %f %f\n", &uv.x, &uv.y);
            //cout<<"UV: "<<uv.x<<" "<<uv.y<<endl;
            temp_uvs.push_back(uv);
        }
            //Process normals at each vertex
        else if (line.substr(0,2)=="vn"){
            vec3 normal;
            values = line.c_str();
            sscanf(values, "vn %f %f %f\n", &normal.x, &normal.y, &normal.z);
            //cout<<"N: "<<normal.x<<" "<<normal.y<<" "<<normal.z<<endl;
            temp_normals.push_back(normal);
        }
            //Process indices of each set of vertices, uvs, and normals.
        else if (line.substr(0,2)=="f "){
            //string vertex1, vertex2, vertex3;
            values = line.c_str();
            int vertexIndex[3], uvIndex[3], normalIndex[3];
            sscanf(values, "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
                   &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                   &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                   &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            //cout<<"F: "<<vertexIndex[0]<<"/"<<uvIndex[0]<<"/"<<normalIndex[0]<<" "
            //    <<vertexIndex[1]<<"/"<<uvIndex[1]<<"/"<<normalIndex[1]<<" "
            //    <<vertexIndex[2]<<"/"<<uvIndex[2]<<"/"<<normalIndex[2]<<endl;
            //if (matches != 9) {
            //    printf("File can't be read by our simple parser :( Try exporting with other options\n");
            //}
            vertexIndices.push_back(vertexIndex[0] - 1);
            vertexIndices.push_back(vertexIndex[1] - 1);
            vertexIndices.push_back(vertexIndex[2] - 1);
            uvIndices.push_back(uvIndex[0] - 1);
            uvIndices.push_back(uvIndex[1] - 1);
            uvIndices.push_back(uvIndex[2] - 1);
            normalIndices.push_back(normalIndex[0] - 1);
            normalIndices.push_back(normalIndex[1] - 1);
            normalIndices.push_back(normalIndex[2] - 1);
        }
    }
    Vertex vertex;

    //Store the file's contents in proper MeshData setup
    for (int i = 0; i < vertexIndices.size(); ++i) {
        //vec3 vertex =
        vertex.Position = temp_vertices[vertexIndices[i]];
        vertex.Normal = temp_normals[normalIndices[i]];
        vertex.uvCoords = temp_uvs[uvIndices[i]];
        meshData.vertices.push_back(vertex);
        //Do we even need the following?
        //meshData.indices.push_back(vertexIndices[i]);
        //meshData.indices.push_back(uvIndices[i]);
        //meshData.indices.push_back(normalIndices[i]);
        //out_vertices.push_back(vertex);
    }
    //// if we made it this far, commit what we have and continue
    //contents = tempContents;
    //filename = filepath;
}

void Model::addTexture(string texturePath){
    //filesystem::path p(texturePath);
    //cout << "filename and extension : " << p.filename() << std::endl; // file.ext
    //cout << "filename only          : " << p.stem() << std::endl;     // file
    Texture texture;
    texture.id=openTexture(texturePath);
    //texture.type=p.stem().string();


}

GLuint Model::openTexture(string filename){
    GLuint textureID;
    int imageLayers, imageWidth, imageHeight;
    //Bind texture
    glGenTextures(1, &textureID);

    unsigned char* image = stbi_load(filename.c_str(), &imageWidth, &imageHeight, &imageLayers, STBI_rgb);

    if(image != nullptr){
        GLenum format;
        if(imageLayers==3){
            format=GL_RGB;
        }
        else if(imageLayers==4){
            format=GL_RGBA;
        }
        else{
            cout<<"Incorrect image format: "<<imageLayers<<endl;
        }
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        //Texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    }
    else{
        cout<<"Failed to load texture: "<< filename<<endl;
        exit(-1);
    }
    stbi_image_free(image);
    return textureID;
}

//Following function based on: https://learnopengl.com/code_viewer.php?code=mesh&type=header
void Model::drawModel() {
    /*  Render data  */
    GLuint VAO, VBO, EBO;

    /*  Functions    */
    // Initializes all the buffer objects/arrays

    // Create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, meshData.vertices.size() * sizeof(Vertex), &meshData.vertices[0], GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.indices.size() * sizeof(GLuint), &meshData.indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uvCoords));
    glBindVertexArray(0);

    // Draw container
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, meshData.vertices.size());
    //glDrawElements(GL_TRIANGLES, meshData.vertices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


//void Model::genImagePlane(){
//    double scaleHeight, scaleWidth;
//
//    if(imageWidth>imageHeight){
//        scaleHeight=(double)imageHeight/imageWidth;
//        scaleWidth=(double)imageWidth/imageWidth;
//    }
//    else if(imageWidth<imageHeight){
//        scaleHeight=(double)imageHeight/imageHeight;
//        scaleWidth=(double)imageWidth/imageHeight;
//    }
//    else{
//        scaleHeight=1;
//        scaleWidth=1;
//    }
//    //cout<<scaleHeight<<":"<<scaleWidth<<endl;
//
//    vector<vector<float>> verticies = {{1.0f,  1.0f, 0.0f},
//                              {1.0f, -1.0f, 0.0f},
//                              {-1.0f, -1.0f, 0.0f},
//                              {-1.0f,  1.0f, 0.0f},};
//    for (int i = 0; i < verticies.size(); ++i) {
//        verticies[i][0]*=scaleWidth;
//        verticies[i][1]*=scaleHeight;
//    }
//    vector<vector<float>> colors = {{1.0f, 0.0f, 0.0f},
//                            {0.0f, 1.0f, 0.0f},
//                            {0.0f, 0.0f, 1.0f},
//                            {1.0f, 1.0f, 0.0f},};
//    vector<vector<float>> uvCoords = {{1.0f, 1.0f},
//                                {1.0f, 0.0f},
//                                {0.0f, 0.0f},
//                                {0.0f, 1.0f},};
//
//    //Create a square using two triangles and the above defined points
//    meshData.vertices = {verticies[0],
//                         verticies[1],
//                         verticies[3],
//
//                         verticies[1],
//                         verticies[2],
//                         verticies[3],
//    };
//    meshData.colors={colors[0],
//                     colors[1],
//                     colors[3],
//
//                     colors[1],
//                     colors[2],
//                     colors[3],
//    };
//    meshData.uvCoords={uvCoords[0],
//                       uvCoords[1],
//                       uvCoords[3],
//
//                       uvCoords[1],
//                       uvCoords[2],
//                       uvCoords[3],
//    };
//}

//vertexArray Model::use() {
//
//    //glBindTexture(GL_TEXTURE_2D, mTexture);
//    vertexArray verts(vertices.size());
//
//    vertexArray verts(meshData.vertices.size()*meshData.vertices[0].size()/3);
//    verts.addBuffer("v", 0, meshData.vertices);
//    verts.addBuffer("c", 1, meshData.colors);
//    verts.addBuffer("t", 2, meshData.uvCoords);
//
//    return verts;
//}
