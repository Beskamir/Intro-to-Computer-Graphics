//
// Created by Sebastian on 29/09/2017.
//

#include "transformations.h"

vector<float> genCurveData(int counter){
    if (counter>1){
        vector<float> curve1 = genCurveData(counter--);

        //All the maths to put points in correct
        //spots and having them in order
        curve1 = shrink(curve1);
        vector<float> curve2 = copy(curve1);
        vector<float> curve3 = copy(curve1);
        curve3 = spin(curve3);
        vector<float> curve4 = copy(curve3);
        curve4 = mirror(curve4);
        curve1 = move(curve1,0.5,0.5);
        curve2 = move(curve2,-0.5,0.5);
        curve3 = move(curve3,-0.5,-0.5);
        curve4 = move(curve4,0.5,-0.5);

        //concatenate them somehow
        vector<float> curve;
        curve.reserve(curve1.size()+curve2.size()+curve3.size()+curve4.size());
        curve.insert(curve1.end(),curve2.begin(),curve3.end,curve4.begin());

        //return the curve
        return curve;
    }
    else{
        //base case return 4 points
        return basePoints;
    }

}

vector<float> points2curve(vector<float>verts){

}

vector<float> points2tris(vector<float>verts){

}

vector<float> shrink(vector<float>verts){

}
vector<float> move(vector<float>verts,float x,float y){

}
vector<float> spin(vector<float>verts){

}

vector<float> copy(vector<float>verts){

}

vector<float> mirror(vector<float>verts){

}


vector<float> getCurve(vector<float>verts){

}
vector<float> getTris(vector<float>verts){

}