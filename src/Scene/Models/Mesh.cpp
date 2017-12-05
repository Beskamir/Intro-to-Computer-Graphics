//
// Mesh data class
//

#include "Mesh.h"

void Mesh::addModel(string filepath) {
    openOBJ(filepath);
    //computeMiddle();
    //moveToOrigin();
}

void Mesh::addTexture(char type, string texturePath) {

}

void Mesh::addTriangle(vector<vec3> point,vec3 normal,vector<vec2> uv) {
    if (uv.empty()){
        uv.emplace_back(vec3(0));
        uv.emplace_back(vec3(0));
        uv.emplace_back(vec3(0));
    }
    for (int i = 0; i < 3; ++i) {
        Vertex vertex;
        vertex.Position = point[i];
        vertex.Normal = normal;
        vertex.uvCoords = uv[i];
        meshData.vertices.push_back(vertex);
    }
}

//following function based on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
bool Mesh::rayTriangleIntersect(const vec3 &vert0, const vec3 &vert1, const vec3 &vert2, Ray &ray, float &tNearTemp, vec2 &uvTemp) {
    vec3 edge1 = vert1 - vert0;
    vec3 edge2 = vert2 - vert0;
    vec3 pVector = cross(ray.getDirection(),edge2);
    float det = dot(edge1, pVector);
    if(det == 0 || det < 0){
        return false;
    }

    vec3 tVector = ray.getOrigin() - vert0;
    uvTemp.x = dot(tVector, pVector);
    if(uvTemp.x<0 || uvTemp.x>det){
        return false;
    }

    vec3 qVector = cross(tVector,edge1);
    uvTemp.y = dot(ray.getDirection(),qVector);
    if(uvTemp.y < 0 || uvTemp.y>det){
        return false;
    }

    tNearTemp = dot(edge2,qVector) / det ;
    uvTemp /= det;
    return true;
}

//following function based on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
bool Mesh::intersect(Ray &ray, float &tNearI, int &indexI, vec2 &uvI) {
    bool intersect = false;
    for (int i = 0; i < meshData.vertices.size()/3; ++i) {
        const vec3 & vert0 = meshData.vertices[i].Position;
        const vec3 & vert1 = meshData.vertices[i+1].Position;
        const vec3 & vert2 =  meshData.vertices[i+2].Position;
        float tNearTemp = tNearI;
        vec2 uvTemp;
        if (rayTriangleIntersect(vert0, vert1, vert2, ray, tNearTemp, uvTemp) && tNearTemp < tNearI) {
            tNearI = tNearTemp;
            uvI = uvTemp;
            indexI = i;
            intersect |= true;
        }
    }
    return intersect;
}

//following function based on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
void Mesh::getSurfaceProperties(vec3 &hitPoint, Ray &ray, int &index, vec2 &uv, vec3 &normal, vec2 &stCoords) {

    const vec3 &v0 = meshData.vertices[index].Position;
    const vec3 &v1 = meshData.vertices[index+1].Position;
    const vec3 &v2 = meshData.vertices[index+2].Position;
    vec3 edge0 = normalize(v1 - v0);
    vec3 edge1 = normalize(v2 - v1);
    normal = normalize(cross(edge0, edge1));
    const vec2 &st0 = meshData.vertices[index].uvCoords;
    const vec2 &st1 = meshData.vertices[index+1].uvCoords;
    const vec2 &st2 = meshData.vertices[index+2].uvCoords;
    stCoords = st0 * (1 - uv.x - uv.y) + st1 * uv.x + st2 * uv.y;

}

//Following function based on:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// https://stackoverflow.com/questions/21120699/c-obj-file-parser
void Mesh::openOBJ(string filename) {
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
            //updateBoundingBox(vertex);
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
        vertex.Position = temp_vertices[vertexIndices[i]];
        vertex.Normal = temp_normals[normalIndices[i]];
        vertex.uvCoords = temp_uvs[uvIndices[i]];
        meshData.vertices.push_back(vertex);
    }
}
