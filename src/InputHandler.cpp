//
// Created by Sebastian on 11/13/2017.
//
#include "InputHandler.h"


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS){
        if (key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    //cout << xoffset << ":"<< yoffset<<endl;
    //if(yoffset>0){
    //    scaleFactor+=scalingSpeed;
    //}
    //if(yoffset<0){
    //    scaleFactor-=scalingSpeed;
    //}
}


void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    //if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
    //    mousePressed=true;
    //    Position currentMouse;
    //    double xpos, ypos;
    //    glfwGetCursorPos(window, &xpos, &ypos);
    //    currentMouse.x=(float)xpos;
    //    currentMouse.y=(float)ypos;
    //    lastMousePos=currentMouse;
    //    //cout << "mouse down" <<endl;
    //}
    //if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
    //    mousePressed=false;
    //    //cout << "mouse up" <<endl;
    //}
    //if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && showControlPoints){
    //}
}


//Position getMouseLocation() {
//    double xpos,ypos;
//    glfwGetCursorPos(window, &xpos,&ypos);
//    Position mouseLocation;
//    mouseLocation.x=(2.0f*((float)(xpos)/(window_width)))-1.0f;
//    mouseLocation.y=1.0f-(2.0f*((float)(ypos)/(window_height)));
//    return mouseLocation;
//}


void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    //if(mousePressed){
    //    Position currentMouse;
    //    currentMouse.x=(float)xpos;
    //    currentMouse.y=(float)ypos;
    //
    //    Position pastMousePos = lastMousePos;
    //
    //    translate.x+=2/scaleFactor*(-pastMousePos.x+currentMouse.x)/window_width;
    //    translate.y+=2/scaleFactor*(pastMousePos.y-currentMouse.y)/window_height;
    //
    //    //Update mouse last positioning
    //    lastMousePos=currentMouse;
    //}
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    //window_width=width;
    //window_height=height;
}
