//
// Created by Sebastian on 29/09/2017.
//

#ifndef ASSIGNMENT1_TRANSFORMATIONS_H
#define ASSIGNMENT1_TRANSFORMATIONS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

//#include "boilerplate.h"

using namespace std;


class Matrix {

public:
    int detailMax;
    int *targetDetail;
    int *windowWidth;
    int *windowHeight;
    int *lineWidth;

    Matrix(int *width, int *height,int *lineSize,int *detail){
        lineWidth = lineSize;
        windowWidth = width;
        windowHeight = height;
        targetDetail = detail;
        //Detail max doesn't really make much sense here tbh
        //if (width<height){
        //    detailMax=(int)floor(log(*windowWidth / *lineWidth)/log(2));
        //}
        //else{
        //    detailMax=(int)floor(log(*windowHeight / *lineWidth)/log(2));
        //}
    }

    void genCurveData(){
        pointData2D = genCurveDataRec(*targetDetail);
    };
    vector<float> getCurve();
    vector<float> getTris();

private:
    const vector<vector<float>> basePoints = {{-0.5, -0.5},
                                              {-0.5, 0.5},
                                              {0.5,  0.5},
                                              {0.5,  -0.5}};

    vector<vector<float>> pointData2D{};

    vector<vector<float>> genCurveDataRec(int counter);

    vector<vector<float>> move(vector<vector<float>>, float x, float y);
    vector<vector<float>> shrink(vector<vector<float>>);
    vector<vector<float>> spin(vector<vector<float>>);
    vector<vector<float>> mirror(vector<vector<float>> verts,bool x,bool y);

    vector<vector<float>> points2tris(vector<vector<float>> verts);

    vector<vector<float>> concatenate(vector<vector<float>> curve1, vector<vector<float>> curve2, vector<vector<float>> curve3, vector<vector<float>> curve4);

};
#endif //ASSIGNMENT1_TRANSFORMATIONS_H
