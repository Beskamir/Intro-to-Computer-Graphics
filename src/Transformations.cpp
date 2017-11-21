//
// Created by Sebastian on 11/20/2017.
//

#include "Transformations.h"

void Transformations::clear() {
    transformation=mat4();
}

mat4 Transformations::getTransformation() {
    return transformation;
}

void Transformations::scale(Transformations::UseAxis useAxis, Mouse mouse) {

    //double scaleFactor = (mouse.getPositivity(mouse.getMouseDifference()) * mouse.getDistance(mouse.getMouseDifference()))/mouse.getDistance(mouse.getMouseLast());

    vec2 mouseAbsPosition = mouse.getMouseDifference(mouse.getMouseCurrent(),vec2(0,0));
    float scaleFactor = (float) (mouse.getPositivity(mouseAbsPosition)
                                 * mouse.getDistance(mouseAbsPosition)
                                 / mouse.getDistance(mouse.getMouseLast()));
    //cout <<scaleFactor<<endl;
    mat4 tempTransform;
    vec3 scalar = vec3(1.0f,1.0f,1.0f);

    if(useAxis.x){
        scalar.x=scaleFactor;
    }
    if(useAxis.y){
        scalar.y=scaleFactor;
    }
    if(useAxis.z){
        scalar.z=scaleFactor;
    }

    tempTransform = glm::scale(tempTransform,scalar);
    transformation = tempTransform;
}
