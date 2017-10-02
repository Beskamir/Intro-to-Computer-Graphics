//
// Created by Sebastian on 29/09/2017.
//

#include <iostream>
#include "transformations.h"

vector<vector<float>> Matrix::genCurveDataRec(int counter){
    if (counter>1){
        vector<vector<float>> curve1 = genCurveDataRec(counter--);

        //All the maths to put points in correct spots and having them in order
        curve1 = shrink(curve1);
        vector<vector<float>> curve2 = copy(curve1);
        vector<vector<float>> curve3 = copy(curve1);
        curve3 = spin(curve3);
        vector<vector<float>> curve4 = copy(curve3);
        curve4 = mirror(curve4);
        curve1 = move(curve1,0.5,0.5);
        curve2 = move(curve2,-0.5,0.5);
        curve3 = move(curve3,-0.5,-0.5);
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

vector<vector<float>> Matrix::points2curve(vector<vector<float>>verts){

}

vector<vector<float>> Matrix::points2tris(vector<vector<float>>verts){

}

vector<vector<float>> Matrix::shrink(vector<vector<float>>verts){

    //go through all pairs and shrink them by 50%
    for (int i = 0; i <= verts.size(); ++i) {
        glm::vec4 vec(verts[i][0], verts[i][1], 0.0f, 1.0f);
        glm::mat4 scaleMatrix;
        scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.5, 0.5, 1.0));
        vec = scaleMatrix * vec;
        verts[i][0]=vec.x;
        verts[i][1]=vec.y;
    }
    return verts;
}
vector<vector<float>> Matrix::move(vector<vector<float>>verts,float x,float y){

}
vector<vector<float>> Matrix::spin(vector<vector<float>>verts){

}

vector<vector<float>> Matrix::copy(vector<vector<float>>verts){

}

vector<vector<float>> Matrix::mirror(vector<vector<float>>verts){

}


vector<float> Matrix::getCurve(){
    vector<float> pointData1D{};
    for (int i = 0; i < pointData2D.size(); ++i) {
        pointData1D.push_back(pointData2D[i][0]);
        pointData1D.push_back(pointData2D[i][1]);
        cout << pointData2D[i][0] << ","<< pointData2D[i][1]<<endl;
        if (i>0 && i<(pointData2D.size()-1)){
            pointData1D.push_back(pointData2D[i][0]);
            pointData1D.push_back(pointData2D[i][1]);
        }
    }
    //for (vector<float> tempMatrix: pointData2D){
    //    for(float tempFloat : tempMatrix){
    //        pointData1D.push_back(tempFloat);
    //    }
    //}
    return pointData1D;

}
vector<float> Matrix::getTris(){

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

//vector<float> Matrix::getPoints() {
//    vector<float> pointData1D{};
//    for(vector<float> point : pointData2D){
//        for(float coordinate:point){
//            pointData1D.push_back(coordinate);
//        }
//    }
//    return pointData1D;
//}

void Matrix::genCurveData() {
    if (detailMax<detailTarget){
        pointData2D = genCurveDataRec(detailMax);
    }
    else{
        pointData2D = genCurveDataRec(detailTarget);
    }
};