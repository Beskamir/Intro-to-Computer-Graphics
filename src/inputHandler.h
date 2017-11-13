//
// Handles all the keyboard and mouse inputs
//

#ifndef ASSIGNMENT2_INPUTHANDLER_H
#define ASSIGNMENT2_INPUTHANDLER_H

void changeColor(int i, float change);

#include "main.h"


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS){
        if (key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if(key==GLFW_KEY_1){
            scalingSpeed=0.005f;
            cout << "Scaling factor set to: " << scalingSpeed<<endl;
        }
        if(key==GLFW_KEY_2 && scalingSpeed>0.005f){
            scalingSpeed -= 0.005f;
            cout << "Scaling factor set to: " << scalingSpeed<<endl;
        }
        if(key==GLFW_KEY_3){
            scalingSpeed=0.025f;
            cout << "Scaling factor set to: " << scalingSpeed<<endl;
        }
        if(key==GLFW_KEY_4 && scalingSpeed<0.1f){
            scalingSpeed += 0.005f;
            cout << "Scaling factor set to: " << scalingSpeed<<endl;
        }
        if(key==GLFW_KEY_5){
            scalingSpeed=0.1f;
            cout << "Scaling factor set to: " << scalingSpeed<<endl;
        }
        if(key==GLFW_KEY_W){
            imageStyle=0;
        }
        if(key==GLFW_KEY_E){
            imageStyle=1;
        }
        if(key==GLFW_KEY_Q){
            imageStyle=2;
        }
        if(key==GLFW_KEY_S){
            if(showControlPoints){
                showControlPoints=false;
            }
            else{
                showControlPoints=true;
            }
        }
        if(showControlPoints){
            if(key==GLFW_KEY_T){
                changeColor(0,0.1f);
                //cout << "Increase red to: " << currentColor[0]<<endl;
            }
            if(key==GLFW_KEY_Y){
                changeColor(1,0.1f);
                //cout << "Increase green to: " << currentColor[1]<<endl;
            }
            if(key==GLFW_KEY_U){
                changeColor(2,0.1f);
                //cout << "Increase blue to: " << currentColor[2]<<endl;
            }

            if(key==GLFW_KEY_G){
                changeColor(0,-0.1f);
                //cout << "Decrease red to: " << currentColor[0]<<endl;
            }
            if(key==GLFW_KEY_H){
                changeColor(1,-0.1f);
                //cout << "Decrease green to: " << currentColor[1]<<endl;
            }
            if(key==GLFW_KEY_J){
                changeColor(2,-0.1f);
                //cout << "Decrease blue to: " << currentColor[2]<<endl;
            }

            int lastCtrlPoints=controlPoints.size()-1;
            if (lastCtrlPoints>=0){
                if(key==GLFW_KEY_L&&controlPoints[lastCtrlPoints].size()>1){
                    convertControlPoints2Spline();
                }
                if(key==GLFW_KEY_O&&controlPoints[lastCtrlPoints].size()>1){
                    convertControlPoints2Loop();
                }
            }
        }
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    //cout << xoffset << ":"<< yoffset<<endl;
    if(yoffset>0){
        scaleFactor+=scalingSpeed;
    }
    if(yoffset<0){
        scaleFactor-=scalingSpeed;
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        mousePressed=true;
        Position currentMouse;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        currentMouse.x=(float)xpos;
        currentMouse.y=(float)ypos;
        lastMousePos=currentMouse;
        //cout << "mouse down" <<endl;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
        mousePressed=false;
        //cout << "mouse up" <<endl;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && showControlPoints){
        addControlPoint();
    }
}

Position getMouseLocation() {
    double xpos,ypos;
    glfwGetCursorPos(window, &xpos,&ypos);
    Position mouseLocation;
    mouseLocation.x=(2.0f*((float)(xpos)/(window_width)))-1.0f;
    mouseLocation.y=1.0f-(2.0f*((float)(ypos)/(window_height)));
    return mouseLocation;
}


void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    if(mousePressed){
        Position currentMouse;
        currentMouse.x=(float)xpos;
        currentMouse.y=(float)ypos;

        Position pastMousePos = lastMousePos;

        translate.x+=2/scaleFactor*(-pastMousePos.x+currentMouse.x)/window_width;
        translate.y+=2/scaleFactor*(pastMousePos.y-currentMouse.y)/window_height;

        //Update mouse last positioning
        lastMousePos=currentMouse;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    window_width=width;
    window_height=height;
}

#endif //ASSIGNMENT2_INPUTHANDLER_H
