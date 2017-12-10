//
// Created by Sebastian on 12/3/2017.
//

#include "Color.h"

Color::Color(float red, float green, float blue, float alpha) {
    r=red;
    g=green;
    b=blue;
    a=alpha;
}

void Color::clampColor(float minValue, float maxValue) {
    r = clampMyMath(minValue, maxValue, r);
    g = clampMyMath(minValue, maxValue, g);
    b = clampMyMath(minValue, maxValue, b);
    a = clampMyMath(minValue, maxValue, a);
}

void Color::applyGammaCorrection(float exposure, float gamma) {
    r = pow(r * exposure, gamma);
    g = pow(g * exposure, gamma);
    b = pow(b * exposure, gamma);
}

Color Color::operator*(float s) {
    return Color(r*s,g*s,b*s,a*s);
}

Color Color::operator+(Color c){
    return Color(c.r+r,c.g+g,c.b+b,c.a+a);
}