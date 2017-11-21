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

void Transformations::rotate(Transformations::UseAxis useAxis, Mouse mouse) {
    vec2 mouseAbsPosition = mouse.getMouseDifference(mouse.getMouseCurrent(),vec2(0,0));
    float angle = (float) (mouse.getDistance(mouseAbsPosition)
                           / mouse.getDistance(mouse.getMouseLast()));
    mat4 tempTransform;
    vec3 gimble = vec3(0.0f,0.0f,0.0f);

    if(useAxis.x){
        gimble.x=1.0f;
    }
    if(useAxis.y){
        gimble.y=1.0f;
    }
    if(useAxis.z){
        gimble.z=1.0f;
    }
    tempTransform = glm::rotate(tempTransform,angle,gimble);
    transformation = tempTransform;
}

void Transformations::translate(Transformations::UseAxis useAxis, Mouse mouse) {
    vec2 mouseAbsPosition = mouse.getMouseDifference(mouse.getMouseCurrent(),vec2(0,0));
    float distance = (float)(mouse.getPositivity(mouseAbsPosition)
                             * (mouse.getDistance(mouseAbsPosition)
                           / mouse.getDistance(mouse.getMouseLast())));

    mat4 tempTransform;
    vec3 translate = vec3(0.0f,0.0f,0.0f);
    if(useAxis.x&&useAxis.y&&useAxis.z){
        translate = vec3(mouseAbsPosition,distance);
    }
    else if(useAxis.x&&useAxis.y){
        translate = vec3(mouseAbsPosition,0.0f);
    }
    else if(useAxis.y&&useAxis.z){
        translate = vec3(0.0f,mouseAbsPosition);
    }
    else if(useAxis.x&&useAxis.z){
        translate = vec3(mouseAbsPosition.x,0.0f,mouseAbsPosition.y);
    }
    else if(useAxis.x){
        translate.x=distance;
    }
    else if(useAxis.y){
        translate.y=distance;
    }
    else if(useAxis.z){
        translate.z=distance;
    }
    tempTransform = glm::translate(tempTransform,translate);
    //transformation = tempTransform;
    transformation = tempTransform;
}
