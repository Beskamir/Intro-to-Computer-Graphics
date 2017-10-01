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

const vector<float> basePoints={  -0.9, -0.9,
                                  -0.9, 0.9,
                                  0.9, 0.9,
                                  0.9, -0.9};

vector<float> genCurveData(int counter);
vector<float> shrink(vector<float>);
vector<float> move(vector<float>,float x, float y);
vector<float> spin(vector<float>);
vector<float> copy(vector<float>verts);
vector<float> mirror(vector<float>verts);

vector<float> getCurve(vector<float>verts);
vector<float> getTris(vector<float>verts);

vector<float> points2curve(vector<float>verts);
vector<float> points2tris(vector<float>verts);


#endif //ASSIGNMENT1_TRANSFORMATIONS_H
