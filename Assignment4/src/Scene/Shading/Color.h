//
// Color class
// Based on:
//      Skeleton code provided with the assignment
//      https://github.com/Hillsoft/Raytracer-Tutorial/tree/master/RayTutNew
//

#ifndef ASSIGNMENT4_COLOR_H
#define ASSIGNMENT4_COLOR_H

#include <cmath>
#include <algorithm>

#include "../../myMath.h"

using namespace std;

class Color {

public:
    float r,g,b,a;
    Color(){r=g=b=a=1.0f;};
    explicit Color(float value){
        r = g = b = value;
        a = 1.0f;
    }
    Color(float r,float g,float b,float a);
    ~Color() = default;

    void clampColor(float minValue = 0.0f, float maxValue = 1.0f);
    void applyGammaCorrection(float exposure, float gamma);

    Color operator + (Color color);
    Color operator * (float s);


};


#endif //ASSIGNMENT4_COLOR_H
