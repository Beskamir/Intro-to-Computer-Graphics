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

void Transformations::scale(bvec3 useAxis, Mouse mouse) {

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
void Transformations::scale(bvec3 useAxis, float scaleFactor) {
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

void Transformations::rotate(bvec3 useAxis, Mouse mouse) {
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

void Transformations::rotate(bvec3 useAxis, float angle) {

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

void Transformations::translate(bvec3 useAxis, vec3 selectedObject, vec3 projectedMousePos) {
    //vec3 mouseAbsPosition = getDistance(projectedMousePos,vec3(0,0,0));
    vec3 mouseAbsPosition = projectedMousePos-selectedObject;
    //float movementRate = 0.05f;
    //if(mouseAbsPosition.x>1){
    //    mouseBasedTranslation.x+=movementRate;
    //}
    //if(mouseAbsPosition.x<1){
    //    mouseBasedTranslation.x-=movementRate;
    //}
    //if(mouseAbsPosition.y>1){
    //    mouseBasedTranslation.y+=movementRate;
    //}
    //if(mouseAbsPosition.y<1){
    //    mouseBasedTranslation.y-=movementRate;
    //}
    //if(mouseAbsPosition.z>1){
    //    mouseBasedTranslation.z+=movementRate;
    //}
    //if(mouseAbsPosition.z<1){
    //    mouseBasedTranslation.z-=movementRate;
    //}

    mat4 tempTransform;
    vec3 translate = vec3(0.0f,0.0f,0.0f);
    if(useAxis.x&&useAxis.y&&useAxis.z){
        translate = vec3(mouseBasedTranslation);
    }
    else if(useAxis.x&&useAxis.y){
        translate = vec3(mouseBasedTranslation.x,mouseBasedTranslation.y,0.0f);
    }
    else if(useAxis.y&&useAxis.z){
        translate = vec3(0.0f,mouseBasedTranslation.y,mouseBasedTranslation.z);
    }
    else if(useAxis.x&&useAxis.z){
        translate = vec3(mouseBasedTranslation.x,0.0f,mouseBasedTranslation.y);
    }
    else if(useAxis.x){
        translate.x=mouseBasedTranslation.x;
    }
    else if(useAxis.y){
        translate.y=mouseBasedTranslation.y;
    }
    else if(useAxis.z){
        translate.z=mouseBasedTranslation.z;
    }
    tempTransform = glm::translate(tempTransform,translate);
    //transformation = tempTransform;
    transformation = tempTransform;
}

void Transformations::translate(bvec3 useAxis, vec3 move) {

    mat4 tempTransform;
    vec3 translate = vec3(0.0f,0.0f,0.0f);
    if(useAxis.x&&useAxis.y&&useAxis.z){
        translate = move;
    }
    else if(useAxis.x&&useAxis.y){
        translate = vec3(move.x,move.y,0.0f);
    }
    else if(useAxis.y&&useAxis.z){
        translate = vec3(0.0f,move.y,move.z);
    }
    else if(useAxis.x&&useAxis.z){
        translate = vec3(move.x,0.0f,move.z);
    }
    else if(useAxis.x){
        translate.x=move.x;
    }
    else if(useAxis.y){
        translate.y=move.y;
    }
    else if(useAxis.z){
        translate.z=move.z;
    }
    tempTransform = glm::translate(tempTransform,translate);
    //transformation = tempTransform;
    transformation = tempTransform;
}