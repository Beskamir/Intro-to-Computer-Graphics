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
    Triangle tempTriangle = {};
    for (int i = 0; i < 3; ++i) {
        //Vertex tempVertex;
        tempTriangle.vertex[i].Position = point[i];
        tempTriangle.vertex[i].Normal = normal;
        tempTriangle.vertex[i].uvCoords = uv[i];
        //cout<<i<<" Pos: "<<point[i].x<<","<<point[i].y<<","<<point[i].z<<endl;
        //tempTriangle.vertex[i]=tempVertex;
    }
    meshData.triangles.push_back(tempTriangle);
}

//following function heavily based on:
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
bool Mesh::rayTriangleIntersect(Triangle &tempTriangle, Ray &ray, float &tNearTemp, vec2 &uvTemp) {
    vec3 v0 = tempTriangle.vertex[0].Position;
    vec3 v1 = tempTriangle.vertex[1].Position;
    vec3 v2 = tempTriangle.vertex[2].Position;

    vec3 v0v1_edge = v1 - v0;
    vec3 v0v2_edge = v2 - v0;

    vec3 pVector = cross(ray.getDirection(),v0v2_edge);
    float determinate = dot(v0v1_edge,pVector);
    if((determinate)<kEpsilon){
        return false;
    }

    float inverseDet = 1/determinate;

    vec3 tVector = ray.getOrigin() - v0;
    uvTemp.x = dot(tVector,pVector) * inverseDet;
    if(uvTemp.x < 0 || uvTemp.x > 1){
        return false;
    }

    vec3 qVector = cross(tVector,v0v1_edge);
    uvTemp.y = dot(ray.getDirection(),qVector) * inverseDet;
    if(uvTemp.y < 0 || uvTemp.x + uvTemp.y >1){
        return false;
    }

    tNearTemp = dot(v0v2_edge,qVector) * inverseDet;
    return true;
}

//following function based on: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview
bool Mesh::intersect(Ray &ray, float &tNearI, int &indexI, vec2 &uvI) {
    bool intersect = false;
    for (int i = 0; i < meshData.triangles.size(); ++i) {
        Triangle tempTriangle = meshData.triangles[i];
        //cout<<"Drawing triangle: "<<i<<endl;
        //const vec3 & vert0 = meshData.triangles[i].vertex[0].Position;
        //const vec3 & vert1 = meshData.triangles[i].vertex[1].Position;
        //const vec3 & vert2 = meshData.triangles[i].vertex[2].Position;
        float tNearTemp = tNearI;
        vec2 uvTemp;
        if (rayTriangleIntersect(tempTriangle, ray, tNearTemp, uvTemp) && tNearTemp < tNearI) {
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

    const vec3 &v0 = meshData.triangles[index].vertex[0].Position;
    const vec3 &v1 = meshData.triangles[index].vertex[1].Position;
    const vec3 &v2 = meshData.triangles[index].vertex[2].Position;
    vec3 edge0 = normalize(v1 - v0);
    vec3 edge1 = normalize(v2 - v1);
    normal = meshData.triangles[index].vertex[1].Normal;
    //normal = normalize(cross(edge0, edge1));
    const vec2 &st0 = meshData.triangles[index].vertex[0].uvCoords;
    const vec2 &st1 = meshData.triangles[index].vertex[1].uvCoords;
    const vec2 &st2 = meshData.triangles[index].vertex[2].uvCoords;
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
    Triangle tempTriangle;
    for (int i = 0; i < vertexIndices.size(); ++i) {
        vertex.Position = temp_vertices[vertexIndices[i]];
        vertex.Normal = temp_normals[normalIndices[i]];
        vertex.uvCoords = temp_uvs[uvIndices[i]];
        //meshData.vertices.push_back(vertex);
        tempTriangle.vertex[i%3] = vertex;
        if((i+1)%3==0){
            meshData.triangles.push_back(tempTriangle);
            //cout<<"writting Verts"<<endl;
        }
    }
}
