//
// Implememtation of all the mathy stuff
//

#include <iostream>
#include "transformations.h"

void Matrix::genCurveData(int targetDetail){
    pointData2D = genCurveDataRec(targetDetail);
    float greenColorValue;
    //Color curve
    for (int i = 0; i < pointData2D.size(); ++i) {
        pointData2D[i].push_back(sinf((float)1-((pointData2D.size()-(float)(i+0.5))/(float)(pointData2D.size()/1.05))));
        greenColorValue=(i/(float)(pointData2D.size()));
        if(greenColorValue<0.5){
            pointData2D[i].push_back(greenColorValue*(float)1.5);
        }
        else{
            pointData2D[i].push_back(((float)0.9-greenColorValue*(float)1.05)*(float)1.75);
        }
        pointData2D[i].push_back(sinf((float)1-(i/(float)(pointData2D.size()/1.5))));
    }
};

vector<vector<float>> Matrix::genCurveDataRec(int counter){
    //cout<<counter<<endl;
    if (counter>1){
        vector<vector<float>> curve1 = genCurveDataRec(--counter);

        //All the maths to put points in correct spots and having them in order
        curve1 = shrink(curve1);
        vector<vector<float>> curve2 = curve1;
        vector<vector<float>> curve3 = curve1;
        curve1 = spin(curve1);
        vector<vector<float>> curve4 = curve1;
        curve1 = mirror(curve1,false,true);
        curve4 = mirror(curve4,true,false);
        curve3 = move(curve3,0.5,0.5);
        curve2 = move(curve2,-0.5,0.5);
        curve1 = move(curve1,-0.5,-0.5);
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

vector<vector<float>> Matrix::shrink(vector<vector<float>>verts){

    float scaleValue=0.5;
    //go through all pairs and shrink them by 50%
    for (int i = 0; i < verts.size(); ++i) {
        glm::vec4 vec(verts[i][0], verts[i][1], 0.0f, 1.0f);
        glm::mat4 transform;
        transform = glm::scale(transform, glm::vec3(scaleValue, scaleValue, 1.0));
        vec = transform * vec;
        verts[i][0]=vec.x;
        verts[i][1]=vec.y;
    }
    return verts;
}
vector<vector<float>> Matrix::move(vector<vector<float>>verts,float x,float y){

    //move objects to specified x,y origin
    for (int i = 0; i < verts.size(); ++i) {
        glm::vec4 vec(verts[i][0], verts[i][1], 0.0f, 1.0f);
        glm::mat4 transform;
        transform = glm::translate(transform, glm::vec3(x, y, 0));
        vec = transform * vec;
        verts[i][0]=vec.x;
        verts[i][1]=vec.y;
    }
    return verts;
}

vector<vector<float>> Matrix::spin(vector<vector<float>>verts){

    // should rotate the object by 90degrees
    for (int i = 0; i < verts.size(); ++i) {
        glm::vec4 vec(verts[i][0], verts[i][1], 0.0f, 1.0f);
        glm::mat4 transform;
        transform = glm::rotate(transform, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
        vec = transform * vec;
        verts[i][0]=vec.x;
        verts[i][1]=vec.y;
    }
    return verts;
}

vector<vector<float>> Matrix::mirror(vector<vector<float>>verts,bool x,bool y){
    if(x){
        for (int i = 0; i < verts.size(); ++i) {
            verts[i][0]=-verts[i][0];
        }
    }
    if(y){
        for (int i = 0; i < verts.size(); ++i) {
            verts[i][1]=-verts[i][1];
        }
    }
    return verts;
}


vector<vector<float>> Matrix::getCurve(){
    vector<vector<float>> curveData{};
    for (int i = 0; i < pointData2D.size(); ++i) {
        curveData.push_back({pointData2D[i][0],pointData2D[i][1],pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
        //cout << pointData2D[i][0] << ","<< pointData2D[i][1]<<endl;
        if (i>0 && i < (pointData2D.size()-1)){
            curveData.push_back({pointData2D[i][0],pointData2D[i][1],pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
        }
    }
    return curveData;

}

//Get triangles
vector<vector<float>> Matrix::getTris(float lineSize){
    vector<vector<float>> trisPointDataRaw=points2tris(lineSize);
    vector<vector<float>> trisPointData{};

    for (int j = 0; j < trisPointDataRaw.size(); ++j) {
        trisPointData.push_back(trisPointDataRaw[j]);

        if(j>2){
            trisPointData.push_back(trisPointDataRaw[j-1]);
            trisPointData.push_back(trisPointDataRaw[j-2]);
        }
        //"clever" (aka horrific) workaround to draw multiple triangles ontop of each other
        // so you don't have to worry about the order in which the vertices might end up in
        if(j>4&&j%2!=0){
            trisPointData.push_back(trisPointDataRaw[j]);
            trisPointData.push_back(trisPointDataRaw[j-1]);
            trisPointData.push_back(trisPointDataRaw[j-3]);
        }
    }
    return trisPointData;

    //return pointData1D;
}

vector<vector<float>> Matrix::points2tris(float lineSize){
    vector<vector<float>> trisPointData{};
    float slope;
    for (int i = 0; i < pointData2D.size(); ++i) {
        if(i>0&&i<(pointData2D.size()-1)){
            if((pointData2D[i+1][1]-pointData2D[i-1][1])==0){
                //0 slope
                trisPointData.push_back({pointData2D[i][0],pointData2D[i][1]+lineSize,
                                         pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
                trisPointData.push_back({pointData2D[i][0],pointData2D[i][1]-lineSize,
                                         pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
            }
            else if((pointData2D[i+1][0]-pointData2D[i-1][0])==0){
                //Infinite slope
                trisPointData.push_back({pointData2D[i][0]-lineSize,
                                         pointData2D[i][1],pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
                trisPointData.push_back({pointData2D[i][0]+lineSize,
                                         pointData2D[i][1],pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
            }
            else{
                //compute slope of the points around the point of interest and flip it
                slope= -((pointData2D[i+1][1]-pointData2D[i-1][1])/(pointData2D[i+1][0]-pointData2D[i-1][0]));
                if(slope<0){
                    //Negative slope
                    trisPointData.push_back({pointData2D[i][0]-lineSize,pointData2D[i][1]+lineSize,
                                             pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
                    trisPointData.push_back({pointData2D[i][0]+lineSize,pointData2D[i][1]-lineSize,
                                             pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
                }
                else{
                    //Positive slope
                    trisPointData.push_back({pointData2D[i][0]+lineSize,pointData2D[i][1]+lineSize,
                                             pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
                    trisPointData.push_back({pointData2D[i][0]-lineSize,pointData2D[i][1]-lineSize,
                                             pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
                }
            }
        }
        //Following if statements only work thanks to short-circuiting evaluation.
        // Essentially if i==0 or i!=0 it doesn't try the other conditional
        else if((i==0)&&(pointData2D[i][0])!=(pointData2D[i+1][0])){
            //slop==0
            trisPointData.push_back({pointData2D[i][0],pointData2D[i][1]+lineSize,
                                     pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
            trisPointData.push_back({pointData2D[i][0],pointData2D[i][1]-lineSize,
                                     pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
        }
        else if((i==(pointData2D.size()-1))&&(pointData2D[i-1][0])!=(pointData2D[i][0])){
            //Infinite slope
            trisPointData.push_back({pointData2D[i][0],pointData2D[i][1]-lineSize,
                                     pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
            trisPointData.push_back({pointData2D[i][0],pointData2D[i][1]+lineSize,
                                     pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
        }
        else if(i==0){
            //infinite slope
            trisPointData.push_back({pointData2D[i][0]-lineSize,pointData2D[i][1],
                                     pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
            trisPointData.push_back({pointData2D[i][0]+lineSize,pointData2D[i][1],
                                     pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
        }
        else{
            //infinite slope
            trisPointData.push_back({pointData2D[i][0]+lineSize,pointData2D[i][1],
                                     pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
            trisPointData.push_back({pointData2D[i][0]-lineSize,pointData2D[i][1],
                                     pointData2D[i][2],pointData2D[i][3],pointData2D[i][4]});
        }
    }
    return trisPointData;
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