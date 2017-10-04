//
// Created by Sebastian on 29/09/2017.
//

#ifndef ASSIGNMENT1_TRANSFORMATIONS_H
#define ASSIGNMENT1_TRANSFORMATIONS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace std;


class Matrix {

public:

    Matrix()= default;

    void genCurveData(int targetDetail){
        pointData2D = genCurveDataRec(targetDetail);
    };
    vector<float> getCurve();
    vector<float> getTris(float lineSize);

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

    vector<vector<float>> points2tris(float lineSize);

    vector<vector<float>> concatenate(vector<vector<float>> curve1, vector<vector<float>> curve2, vector<vector<float>> curve3, vector<vector<float>> curve4);

};
#endif //ASSIGNMENT1_TRANSFORMATIONS_H
