//
// Created by Sebastian on 29/09/2017.
//

#include "transformations.h"

vector<vector<float>> genCurveData(int counter){
    if (counter>1){
        vector<vector<float>> curve1 = genCurveData(counter--);

        //All the maths to put points in correct
        //spots and having them in order
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

vector<vector<float>> points2curve(vector<vector<float>>verts){

}

vector<vector<float>> points2tris(vector<vector<float>>verts){

}

vector<vector<float>> shrink(vector<vector<float>>verts){

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
vector<vector<float>> move(vector<vector<float>>verts,float x,float y){

}
vector<vector<float>> spin(vector<vector<float>>verts){

}

vector<vector<float>> copy(vector<vector<float>>verts){

}

vector<vector<float>> mirror(vector<vector<float>>verts){

}


vector<vector<float>> getCurve(vector<vector<float>>verts){

}
vector<vector<float>> getTris(vector<vector<float>>verts){

}

vector<vector<float>> concatenate(vector<vector<float>>curve1,vector<vector<float>>curve2,vector<vector<float>>curve3,vector<vector<float>>curve4){
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
};