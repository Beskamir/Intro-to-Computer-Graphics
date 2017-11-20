//
// main function heavily based on: https://learnopengl.com/code_viewer.php?code=getting-started/shaders-using-object
//

#include "main.h"
//#include "setup.h"
//#include "OpenGL_Program.h"



double getPositivity();

int main(int argc, char *argv[]) {
    if(!setupOpenGL()){
        return -1;
    }
    setupWindowCallbacks();

    //OpenGL_Program openGL_program(window);
    openGL_program.init_Program(window, &window_width, &window_height);
    openGL_program.mainRender();

    //Call the mainRender method which actually sets up the verts to be drawn
    //mainRender();
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glBindTexture(GL_TEXTURE_2D, 0);
    glfwDestroyWindow(window);
    glfwTerminate();
    cout << "Closing program" << endl;
    return 0;
}

bool setupOpenGL() {
// initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, "CPSC 453 Assignment 2", nullptr, nullptr);
    //Check that window was properly setup
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

// Initialize GLEW if on windows
#ifdef _WIN32
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        cout << "glew init failed" << endl;
        return false;
    }
#endif
    return true;
}

void setupWindowCallbacks() {
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS){
        if (key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else if(key==GLFW_KEY_F && !(rotateMode || scaleMode || moveMode)){
            mouseLocLast = getMouseLocation();
            fpsMode = !fpsMode;
            movement= {false,false,false,false};
        }
        else if(fpsMode){
            if(key==GLFW_KEY_W){
                movement.forward = true;
                movement.backward = false;
            }if(key==GLFW_KEY_S){
                movement.backward = true;
                movement.forward = false;
            }if(key==GLFW_KEY_A){
                movement.left = true;
                movement.right = false;
            }if(key==GLFW_KEY_D){
                movement.right = true;
                movement.left = false;
            }
        }
        else if(!fpsMode){
            if(key==GLFW_KEY_S && !scaleMode){
                mouseLocLast = getMouseLocation();
                mousePerpendicular = vec2(-mouseLocLast.y,mouseLocLast.x);
                cout << mouseLocLast.x <<":"<<mouseLocLast.y<<endl;
                cout << mousePerpendicular.x << ":" << mousePerpendicular.y<<endl;
                initalMouseDistance = getMouseDistance(mouseLocLast);
                scaleMode = true;
                rotateMode = false;
                moveMode = false;
                useAxis={true,true,true};
            }else if(key==GLFW_KEY_R && !rotateMode){
                mouseLocLast = getMouseLocation();
                rotateMode = true;
                moveMode = false;
                scaleMode = false;
                useAxis={true,true,true};
            }else if(key==GLFW_KEY_G && !moveMode){
                mouseLocLast = getMouseLocation();
                moveMode = true;
                rotateMode = false;
                scaleMode = false;
                useAxis={true,true,true};
            }
            else if(rotateMode||scaleMode||moveMode){
                if(key==GLFW_KEY_LEFT_SHIFT||key==GLFW_KEY_RIGHT_SHIFT){
                    shiftMode=!shiftMode;
                }//Lock to one of the following axis
                else if(key==GLFW_KEY_X){
                    if(shiftMode){
                        useAxis={false, true, true};
                        //cout<<"locking to y,z"<<endl;
                    }else{
                        useAxis={true, false, false};
                        //cout<<"locking to x"<<endl;
                    }
                }else if(key==GLFW_KEY_Y){
                    if(shiftMode){
                        useAxis={true, false, true};
                    }else{
                        useAxis={false, true, false};
                    }
                }else if(key==GLFW_KEY_Z){
                    if(shiftMode){
                        useAxis={true, true, false};
                    }else{
                        useAxis={false, false, true};
                    }
                }else if(key==GLFW_KEY_A){
                    useAxis={true,true,true};
                }
            }
            else if(key==GLFW_KEY_C){
                //Center view on object
                int scaleX = 1;
                int scaleY = 1;
                openGL_program.centerView(scaleX,scaleY);
            }
        }

    }
    if(fpsMode){
        openGL_program.moveCamera(movement.forward, movement.backward, movement.right, movement.left);
    }
    if(action==GLFW_RELEASE){
        cout<<key<<endl;
        if(key==GLFW_KEY_W){
            movement.forward = false;
        }
        else if(key==GLFW_KEY_S){
            movement.backward = false;
        }
        else if(key==GLFW_KEY_A){
            movement.left = false;
        }
        else if(key==GLFW_KEY_D){
            movement.right = false;
        }
    }
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    //cout << xoffset << ":"<< yoffset<<endl;
    float scalingSpeed=0.005f;
    if(yoffset>0){
        openGL_program.changeCameraSpeed(scalingSpeed);
    }
    if(yoffset<0){
        openGL_program.changeCameraSpeed(-scalingSpeed);
    }
}


void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        if(scaleMode||rotateMode||moveMode){
            openGL_program.finalizeTransformation();
        }
        cout << "mouse down" <<endl;
    }
}



vec2 getMouseLocation() {
    double xpos,ypos;
    glfwGetCursorPos(window, &xpos,&ypos);
    vec2 mouseLocation={(2.0f*((float)(xpos)/(window_width)))-1.0f,
                        1.0f-(2.0f*((float)(ypos)/(window_height)))};
    return mouseLocation;
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    if(fpsMode){
        //mouseLocCurrent=getMouseLocation();
        //teleportMouse(xpos,ypos);
        mouseLocCurrent = getMouseLocation();
        openGL_program.rotateView(mouseLocCurrent.x-mouseLocLast.x,
                                  mouseLocCurrent.y-mouseLocLast.y);
        glfwSetCursorPos(window,window_width/2,window_height/2);
        //mouseLocCurrent = getMouseLocation();
        //cout<<mouseLocCurrent.x<<":"<<mouseLocCurrent.y<<endl;
        //cout<<mouseLocLast.x<<":"<<mouseLocLast.y<<endl;
        mouseLocLast = getMouseLocation();
    }
    if(scaleMode){
        teleportMouse(xpos,ypos);
        mouseLocCurrent = getMouseLocation();
        mouseLocCurrent.x*=(abs(xTeleportCounter)+1);
        mouseLocCurrent.y*=(abs(yTeleportCounter)+1);
        double scaleFactor = getPositivity() * getMouseDistance(mouseLocCurrent) / initalMouseDistance;
        //cout<<scaleFactor<<endl;
        vec3 scaleVec(scaleFactor,scaleFactor,scaleFactor);
        openGL_program.scaleModel(scaleVec);
    }
    if(rotateMode){
        mouseLocCurrent = getMouseLocation();
        //openGL_program.rotateModel(mouseLocCurrent.x-mouseLocLast.x,
        //                          mouseLocCurrent.y-mouseLocLast.y);
        //cout<<mouseLocCurrent.x<<":"<<mouseLocCurrent.y<<endl;
        //cout<<mouseLocLast.x<<":"<<mouseLocLast.y<<endl;
        mouseLocLast = mouseLocCurrent;
    }
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

double getPositivity() {
    double expected_y = (mouseLocCurrent.x * (mousePerpendicular.y / mousePerpendicular.x));
    if(mouseLocLast.y>0){
        if (expected_y > mouseLocCurrent.y) {
            return -1;
        } else {
            return 1;
        }
    }else{
        if (expected_y < mouseLocCurrent.y) {
            return -1;
        } else {
            return 1;
        }
    }
}

double getMouseDistance(vec2 mousePosition) {
    return sqrt(pow(mousePosition.x,2)+pow(mousePosition.y,2));
}

void teleportMouse(double xpos, double ypos) {
    mouseLocCurrent=getMouseLocation();
    if (mouseLocCurrent.x < -0.75) {
        xTeleportCounter--;
        glfwSetCursorPos(window, ((0.7 + 1.0) / 2) * window_width, ypos);
        mouseLocLast = getMouseLocation();
    }
    if (mouseLocCurrent.x > 0.75) {
        xTeleportCounter++;
        glfwSetCursorPos(window, ((-0.7 + 1.0) / 2) * window_width, ypos);
        mouseLocLast = getMouseLocation();
    }
    if (mouseLocCurrent.y < -0.75) {
        yTeleportCounter--;
        glfwSetCursorPos(window, xpos, ((0.7 - 1.0) / 2) * -window_height);
        mouseLocLast = getMouseLocation();
    }
    if (mouseLocCurrent.y > 0.75) {
        yTeleportCounter++;
        glfwSetCursorPos(window, xpos, ((-0.7 - 1.0) / 2) * -window_height);
        mouseLocLast = getMouseLocation();
    }
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    //float scaleX = float(window_width)/float(width);
    //float scaleY = float(window_height)/float(height);
    //openGL_program.scaleWithWindow(scaleX,scaleY);
    window_width=width;
    window_height=height;
}