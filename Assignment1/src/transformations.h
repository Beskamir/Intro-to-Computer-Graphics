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
    int detailTarget;
    int *windowWidth;
    int *windowHeight;
    int *lineWidth;

    Matrix(int *width, int *height,int *lineSize){
        lineWidth = lineSize;
        windowWidth=width;
        windowHeight=height;
        if (width<height){
            detailMax=(int)floor(log(*windowWidth / *lineWidth)/log(2));
        }
        else{
            detailMax=(int)floor(log(*windowHeight / *lineWidth)/log(2));
        }
        detailTarget = 1;
    }
    void currentScreenRes(){

    }
    void genCurveData();
    vector<float> getCurve();
    vector<float> getTris();
    void increaseDetail(){
        detailTarget++;
    }
    //vector<float> getPoints();

private:
    const vector<vector<float>> basePoints = {{-0.9, -0.9},
                                              {-0.9, 0.9},
                                              {0.9,  0.9},
                                              {0.9,  -0.9}};

    vector<vector<float>> pointData2D{};

    vector<vector<float>> genCurveDataRec(int counter);
    vector<vector<float>> copy(vector<vector<float>> verts);

    vector<vector<float>> move(vector<vector<float>>, float x, float y);
    vector<vector<float>> shrink(vector<vector<float>>);
    vector<vector<float>> spin(vector<vector<float>>);
    vector<vector<float>> mirror(vector<vector<float>> verts);

    vector<vector<float>> points2curve(vector<vector<float>> verts);
    vector<vector<float>> points2tris(vector<vector<float>> verts);

    vector<vector<float>> concatenate(vector<vector<float>> curve1, vector<vector<float>> curve2, vector<vector<float>> curve3, vector<vector<float>> curve4);

};
#endif //ASSIGNMENT1_TRANSFORMATIONS_H
