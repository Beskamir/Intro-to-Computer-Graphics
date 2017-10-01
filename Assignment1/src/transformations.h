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

const vector<vector<float>> basePoints={ {-0.9, -0.9},
                                 {-0.9, 0.9},
                                 {0.9, 0.9},
                                 {0.9, -0.9}};

vector<vector<float>> genCurveData(int counter);
vector<vector<float>> shrink(vector<vector<float>>);
vector<vector<float>> move(vector<vector<float>>,float x, float y);
vector<vector<float>> spin(vector<vector<float>>);
vector<vector<float>> copy(vector<vector<float>>verts);
vector<vector<float>> mirror(vector<vector<float>>verts);

vector<vector<float>> getCurve(vector<vector<float>>verts);
vector<vector<float>> getTris(vector<vector<float>>verts);

vector<vector<float>> points2curve(vector<vector<float>>verts);
vector<vector<float>> points2tris(vector<vector<float>>verts);

vector<vector<float>> concatenate(vector<vector<float>>curve1,vector<vector<float>>curve2,vector<vector<float>>curve3,vector<vector<float>>curve4);

#endif //ASSIGNMENT1_TRANSFORMATIONS_H
