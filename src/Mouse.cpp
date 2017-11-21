//
// Created by Sebastian on 11/20/2017.
//

#include "Mouse.h"

Mouse::Mouse(GLFWwindow *window, int *window_width, int *window_height) {
    this->window=window;
    this->window_width=window_width;
    this->window_height=window_height;
}

void Mouse::setMouseLast() {
    mouseLastPosition=getMouseLocation();
    mouseLastPerpendicular = getPerpendicular(mouseLastPosition);
}

vec2 Mouse::getMouseLast() {
    return mouseLastPosition;
}

vec2 Mouse::getMouseLocation() {
    double xpos,ypos;
    glfwGetCursorPos(window, &xpos,&ypos);
    vec2 mouseLocation={(2.0f*((float)(xpos)/(*window_width)))-1.0f,
                        1.0f-(2.0f*((float)(ypos)/(*window_height)))};
    return mouseLocation;
}

void Mouse::setMouseCurrent() {
    mouseCurrentPosition=getMouseLocation();
}

vec2 Mouse::getMouseCurrent() {
    return mouseCurrentPosition;
}

vec2 Mouse::getMouseDifference(vec2 mouseFinal, vec2 mouseInitial) {
    return mouseFinal-mouseInitial+(counter*(maxRegion-minRegion));
}

vec2 Mouse::getPerpendicular(vec2 mousePosition) {
    return vec2(-mousePosition.y,mousePosition.x);
}

int Mouse::getPositivity(vec2 mouseAbsPosition){
    double expected_y = (mouseAbsPosition.x * (mouseLastPerpendicular.y / mouseLastPerpendicular.x));
    //double expected_y = (((mouseLocCurrent.x*(abs(xTeleportCounter)+1)) * (mousePerpendicular.y / mousePerpendicular.x))/(abs(yTeleportCounter)+1));
    if(mouseLastPosition.y>0){
        if (expected_y > mouseAbsPosition.y) {
            return -1;
        } else {
            return 1;
        }
    }else{
        if (expected_y < mouseAbsPosition.y ) {
            return -1;
        } else {
            return 1;
        }
    }
}

void Mouse::teleportMouse(double xpos,double ypos){
    //cout<<xpos<<":"<<ypos<<endl;
    float offset = 0.005f;
    if (mouseCurrentPosition.x < -usableScreenSize) {
        counter[0].x--;
        //xTeleportCounter--;
        glfwSetCursorPos(window, ((usableScreenSize-offset + 1.0) / 2) * *window_width, ypos);
    }
    if (mouseCurrentPosition.x > usableScreenSize) {
        counter[0].x++;
        //xTeleportCounter++;
        glfwSetCursorPos(window, ((-usableScreenSize+offset + 1.0) / 2) * *window_width, ypos);
    }
    if (mouseCurrentPosition.y < -usableScreenSize) {
        counter[1].y--;
        //yTeleportCounter--;
        glfwSetCursorPos(window, xpos, ((usableScreenSize-offset - 1.0) / 2) * -*window_height);
    }
    if (mouseCurrentPosition.y > usableScreenSize) {
        counter[1].y++;
        //yTeleportCounter++;
        glfwSetCursorPos(window, xpos, ((-usableScreenSize+offset - 1.0) / 2) * -*window_height);
    }
}


void Mouse::reset() {
    counter = mat2({0,0},{0,0});
}

double Mouse::getDistance(vec2 mousePosition) {
    return sqrt(pow(mousePosition.x,2)+pow(mousePosition.y,2));
}
