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

vec2 Mouse::getMouseDifference() {
    return mouseCurrentPosition-mouseLastPosition;
}
