//
// Created by Sebastian on 29/09/2017.
//

//#include <iostream>
#include "transformations.h"

vector<vector<float>> Matrix::genCurveDataRec(int counter){
    //cout<<counter<<endl;
    if (counter>1){
        vector<vector<float>> curve1 = genCurveDataRec(--counter);

        //All the maths to put points in correct spots and having them in order
        curve1 = shrink(curve1);
        vector<vector<float>> curve2 = curve1;
        vector<vector<float>> curve3 = curve1;
        curve1 = spin(curve1);
        vector<vector<float>> curve4 = curve1;
        curve1 = mirror(curve1,false,true);
        curve4 = mirror(curve4,true,false);
        curve3 = move(curve3,0.5,0.5);
        curve2 = move(curve2,-0.5,0.5);
        curve1 = move(curve1,-0.5,-0.5);
        curve4 = move(curve4,0.5,-0.5);

        //concatenate the vectors
        vector<vector<float>> curve = concatenate(curve1,curve2,curve3,curve4);

        //return the curve
        return curve;
    }
    else{
        //base case return 4 points
        return basePoints;
    }

}



vector<vector<float>> Matrix::shrink(vector<vector<float>>verts){

    float scaleValue=0.5;
    //go through all pairs and shrink them by 50%
    for (int i = 0; i < verts.size(); ++i) {
        glm::vec4 vec(verts[i][0], verts[i][1], 0.0f, 1.0f);
        glm::mat4 transform;
        transform = glm::scale(transform, glm::vec3(scaleValue, scaleValue, 1.0));
        vec = transform * vec;
        verts[i][0]=vec.x;
        verts[i][1]=vec.y;
    }
    return verts;
}
vector<vector<float>> Matrix::move(vector<vector<float>>verts,float x,float y){

    //move objects to specified x,y origin
    for (int i = 0; i < verts.size(); ++i) {
        glm::vec4 vec(verts[i][0], verts[i][1], 0.0f, 1.0f);
        glm::mat4 transform;
        transform = glm::translate(transform, glm::vec3(x, y, 0));
        vec = transform * vec;
        verts[i][0]=vec.x;
        verts[i][1]=vec.y;
    }
    return verts;
}
vector<vector<float>> Matrix::spin(vector<vector<float>>verts){

    // should rotate the object by 90degrees
    for (int i = 0; i < verts.size(); ++i) {
        glm::vec4 vec(verts[i][0], verts[i][1], 0.0f, 1.0f);
        glm::mat4 transform;
        transform = glm::rotate(transform, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
        vec = transform * vec;
        verts[i][0]=vec.x;
        verts[i][1]=vec.y;
    }
    return verts;
}

vector<vector<float>> Matrix::mirror(vector<vector<float>>verts,bool x,bool y){
    if(x){
        for (int i = 0; i < verts.size(); ++i) {
            verts[i][0]=-verts[i][0];
        }
    }
    if(y){
        for (int i = 0; i < verts.size(); ++i) {
            verts[i][1]=-verts[i][1];
        }
    }
    return verts;
}


vector<float> Matrix::getCurve(){
    vector<float> pointData1D{};
    for (int i = 0; i < pointData2D.size(); ++i) {
        pointData1D.push_back(pointData2D[i][0]);
        pointData1D.push_back(pointData2D[i][1]);
        //cout << pointData2D[i][0] << ","<< pointData2D[i][1]<<endl;
        if (i>0 && i<(pointData2D.size()-1)){
            pointData1D.push_back(pointData2D[i][0]);
            pointData1D.push_back(pointData2D[i][1]);
        }
    }
    return pointData1D;

}

//Get triangles
vector<float> Matrix::getTris(float lineSize){
    vector<float> pointData1D{};
    points2tris(lineSize);

    return pointData1D;
}

vector<vector<float>> Matrix::points2tris(float lineSize){
    vector<vector<float>> trisPointData{};
    for (int i = 0; i < pointData2D.size(); ++i) {
        if(!(i>0&&i<(pointData2D.size()-1))){
            //Following if statements only work thanks to lazy evaluation. Essentially if i==0 or i!=0 it doesn't try the other conditional
            if((i==0)&&(pointData2D[i][0])<(pointData2D[i+1][0])){
                trisPointData.push_back({pointData2D[i][0],pointData2D[i][1]+lineSize});
                trisPointData.push_back({pointData2D[i][0], pointData2D[i][1] + lineSize});
            }
            else if((i!=0)&&(pointData2D[i-1][0])<(pointData2D[i][0])){
                trisPointData.push_back({pointData2D[i][0],pointData2D[i][1]+lineSize});
                trisPointData.push_back({pointData2D[i][0], pointData2D[i][1] + lineSize});
            }
            else{
                trisPointData.push_back({pointData2D[i][0]+lineSize,pointData2D[i][1]});
                trisPointData.push_back({pointData2D[i][0]+lineSize,pointData2D[i][1]});
            }
        }
        else{
            if(((pointData2D[i-1][0])==(pointData2D[i][0]))
               &&(abs(pointData2D[i-1][1])>abs(pointData2D[i][1]))
               &&(abs(pointData2D[i][0])>abs(pointData2D[i+1][0]))
               &&((pointData2D[i][1])==(pointData2D[i+1][1]))){
                //generate points using slope -1
            }
            if((abs(pointData2D[i-1][0])>abs(pointData2D[i][0]))
               &&((pointData2D[i-1][1])==(pointData2D[i][1]))
               &&((pointData2D[i][0])==(pointData2D[i+1][0]))
               &&(abs(pointData2D[i][1])<abs(pointData2D[i+1][1]))){
                //generate points using slope -1
            }
            if((abs(pointData2D[i-1][0])>abs(pointData2D[i][0]))
               &&((pointData2D[i-1][1])==(pointData2D[i][1]))
               &&((pointData2D[i][0])>(pointData2D[i+1][0]))
               &&(abs(pointData2D[i][1])==abs(pointData2D[i+1][1]))){
                //Infinite slope
            }
            if((abs(pointData2D[i-1][0])<abs(pointData2D[i][0]))
               &&((pointData2D[i-1][1])==(pointData2D[i][1]))
               &&((pointData2D[i][0])==(pointData2D[i+1][0]))
               &&(abs(pointData2D[i][1])<abs(pointData2D[i+1][1]))){
                //slope = 1
            }

            pointData2D[i][0];
        }
    }
    return trisPointData;
}

vector<vector<float>> Matrix::concatenate(vector<vector<float>>curve1,vector<vector<float>>curve2,vector<vector<float>>curve3,vector<vector<float>>curve4){
    vector<vector<float>> curve{};
    curve.insert(
        curve.end(),
        curve1.begin(),
        curve1.end()
    );
    curve.insert(
        curve.end(),
        curve2.begin(),
        curve2.end()
    );
    curve.insert(
        curve.end(),
        curve3.begin(),
        curve3.end()
    );
    curve.insert(
        curve.end(),
        curve4.begin(),
        curve4.end()
    );
    return curve;
}